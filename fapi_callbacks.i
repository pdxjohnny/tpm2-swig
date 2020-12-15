%module(directors="1") fapi_callbacks
%{
#include "fapi_callbacks.h"
%}

%include "tss2/tss2_rc.h"
%include "tss2/tss2_common.h"
%include "tss2/tss2_tpm2_types.h"

%feature("director") Fapi_Callback_Proxy;

%include "fapi_callbacks.h"

%{
extern "C" {
#include <tss2/tss2_rc.h>
}
%}

%pointer_class(TPM2_RC, TPM2_RC_PTR);
%pointer_class(TSS2_RC, TSS2_RC_PTR);
