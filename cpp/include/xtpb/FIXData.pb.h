// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: FIXData.proto

#ifndef PROTOBUF_FIXData_2eproto__INCLUDED
#define PROTOBUF_FIXData_2eproto__INCLUDED

#include <string>
#include "XTConfig.h"
#include <google/protobuf/stubs/common.h>

#if GOOGLE_PROTOBUF_VERSION < 2007000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please update
#error your headers.
#endif
#if 2007000 < GOOGLE_PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers.  Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)

namespace XT {

// Internal implementation detail -- do not call these.
void XT_COMMON_API protobuf_AddDesc_FIXData_2eproto();
void protobuf_AssignDesc_FIXData_2eproto();
void protobuf_ShutdownFile_FIXData_2eproto();

class FieldBase;
class FieldMetrics;

// ===================================================================

class XT_COMMON_API FieldMetrics : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:XT.FieldMetrics) */ {
 public:
  FieldMetrics();
  virtual ~FieldMetrics();

  FieldMetrics(const FieldMetrics& from);

  inline FieldMetrics& operator=(const FieldMetrics& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FieldMetrics& default_instance();

  void Swap(FieldMetrics* other);

  // implements Message ----------------------------------------------

  inline FieldMetrics* New() const { return New(NULL); }

  FieldMetrics* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FieldMetrics& from);
  void MergeFrom(const FieldMetrics& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(FieldMetrics* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 length = 1;
  bool has_length() const;
  void clear_length();
  static const int kLengthFieldNumber = 1;
  ::google::protobuf::int32 length() const;
  void set_length(::google::protobuf::int32 value);

  // optional int32 checksum = 2;
  bool has_checksum() const;
  void clear_checksum();
  static const int kChecksumFieldNumber = 2;
  ::google::protobuf::int32 checksum() const;
  void set_checksum(::google::protobuf::int32 value);

  // @@protoc_insertion_point(class_scope:XT.FieldMetrics)
 private:
  inline void set_has_length();
  inline void clear_has_length();
  inline void set_has_checksum();
  inline void clear_has_checksum();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::int32 length_;
  ::google::protobuf::int32 checksum_;
  friend void XT_COMMON_API protobuf_AddDesc_FIXData_2eproto();
  friend void protobuf_AssignDesc_FIXData_2eproto();
  friend void protobuf_ShutdownFile_FIXData_2eproto();

  void InitAsDefaultInstance();
  static FieldMetrics* default_instance_;
};
// -------------------------------------------------------------------

class XT_COMMON_API FieldBase : public ::google::protobuf::Message /* @@protoc_insertion_point(class_definition:XT.FieldBase) */ {
 public:
  FieldBase();
  virtual ~FieldBase();

  FieldBase(const FieldBase& from);

  inline FieldBase& operator=(const FieldBase& from) {
    CopyFrom(from);
    return *this;
  }

  inline const ::google::protobuf::UnknownFieldSet& unknown_fields() const {
    return _internal_metadata_.unknown_fields();
  }

  inline ::google::protobuf::UnknownFieldSet* mutable_unknown_fields() {
    return _internal_metadata_.mutable_unknown_fields();
  }

  static const ::google::protobuf::Descriptor* descriptor();
  static const FieldBase& default_instance();

  void Swap(FieldBase* other);

  // implements Message ----------------------------------------------

  inline FieldBase* New() const { return New(NULL); }

  FieldBase* New(::google::protobuf::Arena* arena) const;
  void CopyFrom(const ::google::protobuf::Message& from);
  void MergeFrom(const ::google::protobuf::Message& from);
  void CopyFrom(const FieldBase& from);
  void MergeFrom(const FieldBase& from);
  void Clear();
  bool IsInitialized() const;

  int ByteSize() const;
  bool MergePartialFromCodedStream(
      ::google::protobuf::io::CodedInputStream* input);
  void SerializeWithCachedSizes(
      ::google::protobuf::io::CodedOutputStream* output) const;
  ::google::protobuf::uint8* InternalSerializeWithCachedSizesToArray(
      bool deterministic, ::google::protobuf::uint8* output) const;
  ::google::protobuf::uint8* SerializeWithCachedSizesToArray(::google::protobuf::uint8* output) const {
    return InternalSerializeWithCachedSizesToArray(false, output);
  }
  int GetCachedSize() const { return _cached_size_; }
  private:
  void SharedCtor();
  void SharedDtor();
  void SetCachedSize(int size) const;
  void InternalSwap(FieldBase* other);
  private:
  inline ::google::protobuf::Arena* GetArenaNoVirtual() const {
    return _internal_metadata_.arena();
  }
  inline void* MaybeArenaPtr() const {
    return _internal_metadata_.raw_arena_ptr();
  }
  public:

  ::google::protobuf::Metadata GetMetadata() const;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  // optional int32 field = 1;
  bool has_field() const;
  void clear_field();
  static const int kFieldFieldNumber = 1;
  ::google::protobuf::int32 field() const;
  void set_field(::google::protobuf::int32 value);

  // optional string stringvalue = 2;
  bool has_stringvalue() const;
  void clear_stringvalue();
  static const int kStringvalueFieldNumber = 2;
  const ::std::string& stringvalue() const;
  void set_stringvalue(const ::std::string& value);
  void set_stringvalue(const char* value);
  void set_stringvalue(const char* value, size_t size);
  ::std::string* mutable_stringvalue();
  ::std::string* release_stringvalue();
  void set_allocated_stringvalue(::std::string* stringvalue);

  // optional string data = 3;
  bool has_data() const;
  void clear_data();
  static const int kDataFieldNumber = 3;
  const ::std::string& data() const;
  void set_data(const ::std::string& value);
  void set_data(const char* value);
  void set_data(const char* value, size_t size);
  ::std::string* mutable_data();
  ::std::string* release_data();
  void set_allocated_data(::std::string* data);

  // optional .XT.FieldMetrics metrics = 4;
  bool has_metrics() const;
  void clear_metrics();
  static const int kMetricsFieldNumber = 4;
  const ::XT::FieldMetrics& metrics() const;
  ::XT::FieldMetrics* mutable_metrics();
  ::XT::FieldMetrics* release_metrics();
  void set_allocated_metrics(::XT::FieldMetrics* metrics);

  // @@protoc_insertion_point(class_scope:XT.FieldBase)
 private:
  inline void set_has_field();
  inline void clear_has_field();
  inline void set_has_stringvalue();
  inline void clear_has_stringvalue();
  inline void set_has_data();
  inline void clear_has_data();
  inline void set_has_metrics();
  inline void clear_has_metrics();

  ::google::protobuf::internal::InternalMetadataWithArena _internal_metadata_;
  ::google::protobuf::uint32 _has_bits_[1];
  mutable int _cached_size_;
  ::google::protobuf::internal::ArenaStringPtr stringvalue_;
  ::google::protobuf::internal::ArenaStringPtr data_;
  ::XT::FieldMetrics* metrics_;
  ::google::protobuf::int32 field_;
  friend void XT_COMMON_API protobuf_AddDesc_FIXData_2eproto();
  friend void protobuf_AssignDesc_FIXData_2eproto();
  friend void protobuf_ShutdownFile_FIXData_2eproto();

  void InitAsDefaultInstance();
  static FieldBase* default_instance_;
};
// ===================================================================


// ===================================================================

#if !PROTOBUF_INLINE_NOT_IN_HEADERS
// FieldMetrics

// optional int32 length = 1;
inline bool FieldMetrics::has_length() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FieldMetrics::set_has_length() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FieldMetrics::clear_has_length() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FieldMetrics::clear_length() {
  length_ = 0;
  clear_has_length();
}
inline ::google::protobuf::int32 FieldMetrics::length() const {
  // @@protoc_insertion_point(field_get:XT.FieldMetrics.length)
  return length_;
}
inline void FieldMetrics::set_length(::google::protobuf::int32 value) {
  set_has_length();
  length_ = value;
  // @@protoc_insertion_point(field_set:XT.FieldMetrics.length)
}

// optional int32 checksum = 2;
inline bool FieldMetrics::has_checksum() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FieldMetrics::set_has_checksum() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FieldMetrics::clear_has_checksum() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FieldMetrics::clear_checksum() {
  checksum_ = 0;
  clear_has_checksum();
}
inline ::google::protobuf::int32 FieldMetrics::checksum() const {
  // @@protoc_insertion_point(field_get:XT.FieldMetrics.checksum)
  return checksum_;
}
inline void FieldMetrics::set_checksum(::google::protobuf::int32 value) {
  set_has_checksum();
  checksum_ = value;
  // @@protoc_insertion_point(field_set:XT.FieldMetrics.checksum)
}

// -------------------------------------------------------------------

// FieldBase

// optional int32 field = 1;
inline bool FieldBase::has_field() const {
  return (_has_bits_[0] & 0x00000001u) != 0;
}
inline void FieldBase::set_has_field() {
  _has_bits_[0] |= 0x00000001u;
}
inline void FieldBase::clear_has_field() {
  _has_bits_[0] &= ~0x00000001u;
}
inline void FieldBase::clear_field() {
  field_ = 0;
  clear_has_field();
}
inline ::google::protobuf::int32 FieldBase::field() const {
  // @@protoc_insertion_point(field_get:XT.FieldBase.field)
  return field_;
}
inline void FieldBase::set_field(::google::protobuf::int32 value) {
  set_has_field();
  field_ = value;
  // @@protoc_insertion_point(field_set:XT.FieldBase.field)
}

// optional string stringvalue = 2;
inline bool FieldBase::has_stringvalue() const {
  return (_has_bits_[0] & 0x00000002u) != 0;
}
inline void FieldBase::set_has_stringvalue() {
  _has_bits_[0] |= 0x00000002u;
}
inline void FieldBase::clear_has_stringvalue() {
  _has_bits_[0] &= ~0x00000002u;
}
inline void FieldBase::clear_stringvalue() {
  stringvalue_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_stringvalue();
}
inline const ::std::string& FieldBase::stringvalue() const {
  // @@protoc_insertion_point(field_get:XT.FieldBase.stringvalue)
  return stringvalue_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FieldBase::set_stringvalue(const ::std::string& value) {
  set_has_stringvalue();
  stringvalue_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:XT.FieldBase.stringvalue)
}
inline void FieldBase::set_stringvalue(const char* value) {
  set_has_stringvalue();
  stringvalue_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:XT.FieldBase.stringvalue)
}
inline void FieldBase::set_stringvalue(const char* value, size_t size) {
  set_has_stringvalue();
  stringvalue_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:XT.FieldBase.stringvalue)
}
inline ::std::string* FieldBase::mutable_stringvalue() {
  set_has_stringvalue();
  // @@protoc_insertion_point(field_mutable:XT.FieldBase.stringvalue)
  return stringvalue_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FieldBase::release_stringvalue() {
  // @@protoc_insertion_point(field_release:XT.FieldBase.stringvalue)
  clear_has_stringvalue();
  return stringvalue_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FieldBase::set_allocated_stringvalue(::std::string* stringvalue) {
  if (stringvalue != NULL) {
    set_has_stringvalue();
  } else {
    clear_has_stringvalue();
  }
  stringvalue_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), stringvalue);
  // @@protoc_insertion_point(field_set_allocated:XT.FieldBase.stringvalue)
}

// optional string data = 3;
inline bool FieldBase::has_data() const {
  return (_has_bits_[0] & 0x00000004u) != 0;
}
inline void FieldBase::set_has_data() {
  _has_bits_[0] |= 0x00000004u;
}
inline void FieldBase::clear_has_data() {
  _has_bits_[0] &= ~0x00000004u;
}
inline void FieldBase::clear_data() {
  data_.ClearToEmptyNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
  clear_has_data();
}
inline const ::std::string& FieldBase::data() const {
  // @@protoc_insertion_point(field_get:XT.FieldBase.data)
  return data_.GetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FieldBase::set_data(const ::std::string& value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), value);
  // @@protoc_insertion_point(field_set:XT.FieldBase.data)
}
inline void FieldBase::set_data(const char* value) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), ::std::string(value));
  // @@protoc_insertion_point(field_set_char:XT.FieldBase.data)
}
inline void FieldBase::set_data(const char* value, size_t size) {
  set_has_data();
  data_.SetNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(),
      ::std::string(reinterpret_cast<const char*>(value), size));
  // @@protoc_insertion_point(field_set_pointer:XT.FieldBase.data)
}
inline ::std::string* FieldBase::mutable_data() {
  set_has_data();
  // @@protoc_insertion_point(field_mutable:XT.FieldBase.data)
  return data_.MutableNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline ::std::string* FieldBase::release_data() {
  // @@protoc_insertion_point(field_release:XT.FieldBase.data)
  clear_has_data();
  return data_.ReleaseNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited());
}
inline void FieldBase::set_allocated_data(::std::string* data) {
  if (data != NULL) {
    set_has_data();
  } else {
    clear_has_data();
  }
  data_.SetAllocatedNoArena(&::google::protobuf::internal::GetEmptyStringAlreadyInited(), data);
  // @@protoc_insertion_point(field_set_allocated:XT.FieldBase.data)
}

// optional .XT.FieldMetrics metrics = 4;
inline bool FieldBase::has_metrics() const {
  return (_has_bits_[0] & 0x00000008u) != 0;
}
inline void FieldBase::set_has_metrics() {
  _has_bits_[0] |= 0x00000008u;
}
inline void FieldBase::clear_has_metrics() {
  _has_bits_[0] &= ~0x00000008u;
}
inline void FieldBase::clear_metrics() {
  if (metrics_ != NULL) metrics_->::XT::FieldMetrics::Clear();
  clear_has_metrics();
}
inline const ::XT::FieldMetrics& FieldBase::metrics() const {
  // @@protoc_insertion_point(field_get:XT.FieldBase.metrics)
  return metrics_ != NULL ? *metrics_ : *default_instance_->metrics_;
}
inline ::XT::FieldMetrics* FieldBase::mutable_metrics() {
  set_has_metrics();
  if (metrics_ == NULL) {
    metrics_ = new ::XT::FieldMetrics;
  }
  // @@protoc_insertion_point(field_mutable:XT.FieldBase.metrics)
  return metrics_;
}
inline ::XT::FieldMetrics* FieldBase::release_metrics() {
  // @@protoc_insertion_point(field_release:XT.FieldBase.metrics)
  clear_has_metrics();
  ::XT::FieldMetrics* temp = metrics_;
  metrics_ = NULL;
  return temp;
}
inline void FieldBase::set_allocated_metrics(::XT::FieldMetrics* metrics) {
  delete metrics_;
  metrics_ = metrics;
  if (metrics) {
    set_has_metrics();
  } else {
    clear_has_metrics();
  }
  // @@protoc_insertion_point(field_set_allocated:XT.FieldBase.metrics)
}

#endif  // !PROTOBUF_INLINE_NOT_IN_HEADERS
// -------------------------------------------------------------------


// @@protoc_insertion_point(namespace_scope)

}  // namespace XT

// @@protoc_insertion_point(global_scope)

 
 
#endif  // PROTOBUF_FIXData_2eproto__INCLUDED
