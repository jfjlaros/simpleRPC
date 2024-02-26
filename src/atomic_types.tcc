#pragma once

#include "Arduino.h"
#include "string.h"
#include "TString.tcc"

//! \defgroup types

template<class T>
struct RpcAtomicType
{
  static constexpr char  getType()
  {
    static_assert(always_false<T>::value, "type not supported by simpleRPC");
    return '\0';
  }
};

template<typename T>
constexpr bool check_supported_rpc_type() {
    return std::is_same<T, bool>::value ||
           std::is_same<T, char>::value ||
           std::is_same<T, int8_t>::value ||
           std::is_same<T, uint8_t>::value ||
           std::is_same<T, int16_t>::value ||
           std::is_same<T, uint16_t>::value ||
           std::is_same<T, int32_t>::value;
           std::is_same<T, uint32_t>::value ||
           std::is_same<T, int64_t>::value ||
           std::is_same<T, uint64_t>::value ||
           std::is_same<T, float>::value ||
           std::is_same<T, double>::value ||
           std::is_same<T, char*>::value ||
           std::is_same<T, const char*>::value ||
           std::is_same<T, String>::value ||
           std::is_same<T, String&>::value ||
           std::is_same<T, PString>::value ||
           std::is_same<T, PString&>::value;
            
            }

// Define a variable template for easier use.
template<typename T>
constexpr bool isAtomicType = check_supported_rpc_type<T>();

// Helper type to check if getType() is valid for T
template<typename T>
struct RpcAtomicTypeHelper
{
  static bool isAtomicType() { return false;}
};

template<> struct RpcAtomicTypeHelper<bool>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<char>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<int8_t>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<uint8_t>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<int16_t>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<uint16_t>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<int32_t>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<uint32_t>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<int64_t>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<uint64_t>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<float>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<double>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<char*>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<const char*>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<String>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<String&>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<PString>{ static bool isAtomicType() { return true; }};
template<> struct RpcAtomicTypeHelper<PString&>{ static bool isAtomicType() { return true; }};
template<size_t S> struct RpcAtomicTypeHelper<TString<S>>{ static bool isAtomicType() { return true; }};
template<size_t S> struct RpcAtomicTypeHelper<TString<S>&>{ static bool isAtomicType() { return true; }};


template<> struct RpcAtomicType<bool> {  static constexpr char  getType() { return '?'; } };
template<> struct RpcAtomicType<char> {  static constexpr char  getType() { return 'c'; } };
template<> struct RpcAtomicType<int8_t> {  static constexpr char  getType() { return 'b'; } };
template<> struct RpcAtomicType<uint8_t> {  static constexpr char  getType() { return 'B'; } };
template<> struct RpcAtomicType<int16_t> {  static constexpr char  getType() { return 'h'; } };
template<> struct RpcAtomicType<uint16_t> {  static constexpr char  getType() { return 'H'; } };
template<> struct RpcAtomicType<int32_t> {  static constexpr char  getType() { return 'i'; } };
template<> struct RpcAtomicType<int>
{
  static constexpr char  getType()
  {
    if (sizeof(int) == 4) return 'i';
    else return 'h';
  }
};

template<> struct RpcAtomicType<uint32_t> {  static constexpr char  getType() { return 'I'; } };
template<> struct RpcAtomicType<unsigned int>
{
  static constexpr char  getType()
  {
    if (sizeof(unsigned int) == 4) return 'I';
    else return 'H';
  }
};

template<> struct RpcAtomicType<int64_t> {  static constexpr char  getType() { return 'q'; } };
template<> struct RpcAtomicType<uint64_t> {  static constexpr char  getType() { return 'Q'; } };
template<> struct RpcAtomicType<float> {  static constexpr char  getType() { return 'f'; } };
template<> struct RpcAtomicType<double>
{
  static constexpr char  getType()
  {
    if (sizeof(double) == 4) return 'f';
    else return 'd';
  }
};

template<> struct RpcAtomicType<char*> {  static constexpr char  getType() { return 's'; } };
template<> struct RpcAtomicType<const char*> {  static constexpr char  getType() { return 's'; } };
template<> struct RpcAtomicType<String> {  static constexpr char  getType() { return 's'; } };
template<> struct RpcAtomicType<String&> {  static constexpr char  getType() { return 's'; } };
template<> struct RpcAtomicType<PString> {  static constexpr char  getType() { return 's'; } };
template<> struct RpcAtomicType<PString&> {  static constexpr char  getType() { return 's'; } };
template<size_t S> struct RpcAtomicType<TString<S>> {  static constexpr char  getType() { return 's'; } };
template<size_t S> struct RpcAtomicType<TString<S>&> {  static constexpr char  getType() { return 's'; } };
