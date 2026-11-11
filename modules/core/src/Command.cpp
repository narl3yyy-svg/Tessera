#include "tsr/core/Command.h"

#include <cmath>
#include <sstream>

namespace tsr {

const InputDef* CommandDef::input(const std::string& inputId) const {
  for (const auto& d : inputs)
    if (d.id == inputId) return &d;
  return nullptr;
}

namespace {
template <class T>
const T& get(const Inputs& in, const std::string& id, const char* typeName) {
  auto it = in.find(id);
  if (it == in.end()) throw std::invalid_argument("missing input '" + id + "'");
  if (auto p = std::get_if<T>(&it->second)) return *p;
  throw std::invalid_argument("input '" + id + "' is not " + typeName);
}
} // namespace

double getReal(const Inputs& in, const std::string& id) {
  auto it = in.find(id);
  if (it != in.end())
    if (auto i = std::get_if<std::int64_t>(&it->second)) return static_cast<double>(*i);
  return get<double>(in, id, "a real");
}
std::int64_t getInt(const Inputs& in, const std::string& id) { return get<std::int64_t>(in, id, "an integer"); }
bool getBool(const Inputs& in, const std::string& id) { return get<bool>(in, id, "a bool"); }
const std::string& getString(const Inputs& in, const std::string& id) { return get<std::string>(in, id, "a string"); }

CommandSession::CommandSession(const Command& cmd, CommandContext& ctx) : cmd_(cmd), ctx_(ctx) {
  for (const auto& d : cmd_.def().inputs) inputs_[d.id] = d.defaultValue;
}

CommandSession::CommandSession(const Command& cmd, CommandContext& ctx, const Inputs& initial)
    : CommandSession(cmd, ctx) {
  for (const auto& [k, v] : initial)
    if (cmd_.def().input(k)) inputs_[k] = v;
}

CommandSession::~CommandSession() {
  if (!finished_) cancel();
}

std::string CommandSession::checkInput(const InputDef& d, const Value& v) const {
  switch (d.type) {
    case InputType::Real: {
      double x;
      if (auto p = std::get_if<double>(&v)) x = *p;
      else if (auto i = std::get_if<std::int64_t>(&v)) x = static_cast<double>(*i);
      else return d.label + ": expected a number";
      if (!std::isfinite(x)) return d.label + ": value is not finite";
      std::ostringstream os;
      if (d.min && (x < *d.min || (d.minExclusive && x == *d.min))) {
        os << d.label << ": must be " << (d.minExclusive ? "greater than " : "at least ")
           << formatQuantity(*d.min, d.unit);
        return os.str();
      }
      if (d.max && x > *d.max) {
        os << d.label << ": must be at most " << formatQuantity(*d.max, d.unit);
        return os.str();
      }
      return {};
    }
    case InputType::Integer: {
      auto p = std::get_if<std::int64_t>(&v);
      if (!p) return d.label + ": expected an integer";
      if (d.min && *p < *d.min) return d.label + ": too small";
      if (d.max && *p > *d.max) return d.label + ": too large";
      return {};
    }
    case InputType::Bool:
      return std::holds_alternative<bool>(v) ? std::string{} : d.label + ": expected true/false";
    case InputType::String:
    case InputType::Body:
    case InputType::Sketch:
    case InputType::Profiles:
    case InputType::Edges: {
      auto p = std::get_if<std::string>(&v);
      if (!p) return d.label + ": expected text";
      if (p->empty() && !d.optional)
        return d.label + (d.type == InputType::Body    ? ": select a body"
                          : d.type == InputType::Edges ? ": select one or more edges in the canvas"
                                                       : ": required");
      return {};
    }
    case InputType::Choice: {
      auto p = std::get_if<std::string>(&v);
      if (!p) return d.label + ": expected one of the listed options";
      for (const auto& c : d.choices)
        if (c == *p) return {};
      std::string opts;
      for (const auto& c : d.choices) opts += (opts.empty() ? "" : ", ") + c;
      return d.label + ": '" + *p + "' is not one of " + opts;
    }
  }
  return "unknown input type";
}

std::string CommandSession::setInput(const std::string& id, const Value& v) {
  const InputDef* d = cmd_.def().input(id);
  if (!d) return "unknown input '" + id + "'";
  if (auto err = checkInput(*d, v); !err.empty()) return err;
  dropPreview();
  inputs_[id] = (d->type == InputType::Real && std::holds_alternative<std::int64_t>(v))
                    ? Value(static_cast<double>(std::get<std::int64_t>(v)))
                    : v;
  return {};
}

std::string CommandSession::validate() {
  for (const auto& d : cmd_.def().inputs)
    if (auto err = checkInput(d, inputs_.at(d.id)); !err.empty()) return err;
  try {
    return cmd_.validate(inputs_, ctx_);
  } catch (const std::exception& e) {
    return e.what();
  }
}

void CommandSession::dropPreview() {
  if (previewActive_) {
    ctx_.abortTransaction();
    previewActive_ = false;
  }
}

std::string CommandSession::preview() {
  if (finished_) return "command already finished";
  dropPreview();
  if (!cmd_.supportsPreview()) return {};
  if (auto err = validate(); !err.empty()) return err;
  if (auto err = applyInTransaction(cmd_.def().name + " (preview)"); !err.empty()) return err;
  previewActive_ = true;
  return {};
}

std::string CommandSession::applyInTransaction(const std::string& name) {
  ctx_.openTransaction(name);
  try {
    cmd_.prepare(inputs_, ctx_);
    cmd_.apply(inputs_, ctx_);
    if (cmd_.def().feature) ctx_.recordFeature(cmd_, inputs_);
  } catch (const std::exception& e) {
    ctx_.abortTransaction();
    return e.what();
  }
  return {};
}

std::string CommandSession::execute() {
  if (finished_) return "command already finished";
  dropPreview();
  if (auto err = validate(); !err.empty()) return err;
  if (auto err = applyInTransaction(cmd_.def().name); !err.empty()) return err;
  ctx_.commitTransaction();
  finished_ = true;
  return {};
}

void CommandSession::cancel() {
  dropPreview();
  finished_ = true;
}

} // namespace tsr
