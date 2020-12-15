/* File : example.h */

#include <iostream>

extern "C" {
#include <tss2/tss2_fapi.h>
}


class Fapi_Callback_Proxy {
public:
	virtual ~Fapi_Callback_Proxy() { std::cout << "Fapi_Callback_Proxy::~Fapi_Callback_Proxy()" << std:: endl; }
	virtual void Fapi_CB_Auth(
    char    const *objectPath,
    char    const *description,
    char    const **auth,
    TSS2_RC       *rc) {}
};



class Caller {
public:
	Fapi_Callback_Proxy *callback;
	Caller(): callback(0) {}
	~Caller() { delCallback(); }
	void delCallback() { if (callback) delete callback; callback = 0; }
	void setCallback(Fapi_Callback_Proxy *cb) { delCallback(); callback = cb; }
	TSS2_RC SetAuthCB_Fapi(FAPI_CONTEXT *context) {
    return Fapi_SetAuthCB(context, this->Fapi_CB_Auth_Proxy, (void *)this);
  }
  static TSS2_RC Fapi_CB_Auth_Proxy(
    char    const  *objectPath,
    char    const  *description,
    char    const **auth,
    void           *userData)
  {
    TSS2_RC rc = TPM2_RC_FAILURE;

    ((Caller *)userData)->callback->Fapi_CB_Auth(objectPath, description, auth, &rc);

    return rc;
  }
};
/*
typedef TSS2_RC (*Fapi_CB_Auth)(
    char     const *objectPath,
    char     const *description,
    char          **auth,
    void           *userData);

typedef TSS2_RC (*Fapi_CB_Branch)(
    FAPI_CONTEXT   *context,
    char     const *description,
    char    const **branchNames,
    size_t          numBranches,
    size_t         *selectedBranch,
    void           *userData);

typedef TSS2_RC (*Fapi_CB_Sign)(
    FAPI_CONTEXT   *context,
    char     const *description,
    char     const *publicKey,
    char     const *publicKeyHint,
    uint32_t        hashAlg,
    uint8_t  const *dataToSign,
    size_t          dataToSignSize,
    uint8_t       **signature,
    size_t         *signatureSize,
    void           *userData);

typedef TSS2_RC (*Fapi_CB_PolicyAction)(
    FAPI_CONTEXT   *context,
    char     const *action,
    void           *userData);
*/
