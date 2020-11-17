%module(directors="1") fapi_callbacks
%{
#include "fapi_callbacks.h"
%}

%feature("director") Fapi_Callback_Proxy;

%include "fapi_callbacks.h"
