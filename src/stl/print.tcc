#ifndef SIMPLE_RPC_STL_PRINT_TCC_
#define SIMPLE_RPC_STL_PRINT_TCC_

//! \defgroup STLPrint


/*! \ingroup STLPrint
 * \copydoc rpcPrint(Stream&, T) */
inline void rpcPrint(Stream& io, std::string& data) {
  rpcPrint(io, (String&)data);
}

#endif
