/* soapStub.h
   Generated by gSOAP 2.8.84 for WeatherService.h

gSOAP XML Web services tools
Copyright (C) 2000-2018, Robert van Engelen, Genivia Inc. All Rights Reserved.
The soapcpp2 tool and its generated software are released under the GPL.
This program is released under the GPL with the additional exemption that
compiling, linking, and/or using OpenSSL is allowed.
--------------------------------------------------------------------------------
A commercial use license is available from Genivia Inc., contact@genivia.com
--------------------------------------------------------------------------------
*/

#include <vector>
#define SOAP_NAMESPACE_OF_ns1	"http://WebXml.com.cn/"

#ifndef soapStub_H
#define soapStub_H
#include "stdsoap2.h"
#if GSOAP_VERSION != 20884
# error "GSOAP VERSION 20884 MISMATCH IN GENERATED CODE VERSUS LIBRARY CODE: PLEASE REINSTALL PACKAGE"
#endif


/******************************************************************************\
 *                                                                            *
 * Types with Custom Serializers                                              *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Classes, Structs and Unions                                                *
 *                                                                            *
\******************************************************************************/

class _ns1__qqCheckOnline;	/* WeatherService.h:162 */
class _ns1__qqCheckOnlineResponse;	/* WeatherService.h:164 */
struct __ns1__qqCheckOnline;	/* WeatherService.h:396 */
struct __ns1__qqCheckOnline_;	/* WeatherService.h:469 */

/* WeatherService.h:162 */
#ifndef SOAP_TYPE__ns1__qqCheckOnline
#define SOAP_TYPE__ns1__qqCheckOnline (8)
/* complex XML schema type 'ns1:qqCheckOnline': */
class SOAP_CMAC _ns1__qqCheckOnline {
      public:
        /// Optional element 'ns1:qqCode' of XML schema type 'xsd:string'
        std::string *qqCode;
        /// Context that manages this object
        struct soap *soap;
      public:
        /// Return unique type id SOAP_TYPE__ns1__qqCheckOnline
        virtual long soap_type(void) const { return SOAP_TYPE__ns1__qqCheckOnline; }
        /// (Re)set members to default values
        virtual void soap_default(struct soap*);
        /// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
        virtual void soap_serialize(struct soap*) const;
        /// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
        virtual int soap_put(struct soap*, const char *tag, const char *type) const;
        /// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
        virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
        /// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
        virtual void *soap_get(struct soap*, const char *tag, const char *type);
        /// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
        virtual void *soap_in(struct soap*, const char *tag, const char *type);
        /// Return a new object of type _ns1__qqCheckOnline, default initialized and not managed by a soap context
        virtual _ns1__qqCheckOnline *soap_alloc(void) const { return SOAP_NEW_UNMANAGED(_ns1__qqCheckOnline); }
      public:
        /// Constructor with default initializations
        _ns1__qqCheckOnline() : qqCode(), soap() { }
        virtual ~_ns1__qqCheckOnline() { }
        /// Friend allocator used by soap_new__ns1__qqCheckOnline(struct soap*, int)
        friend SOAP_FMAC1 _ns1__qqCheckOnline * SOAP_FMAC2 soap_instantiate__ns1__qqCheckOnline(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* WeatherService.h:164 */
#ifndef SOAP_TYPE__ns1__qqCheckOnlineResponse
#define SOAP_TYPE__ns1__qqCheckOnlineResponse (9)
/* complex XML schema type 'ns1:qqCheckOnlineResponse': */
class SOAP_CMAC _ns1__qqCheckOnlineResponse {
      public:
        /// Optional element 'ns1:qqCheckOnlineResult' of XML schema type 'xsd:string'
        std::string *qqCheckOnlineResult;
        /// Context that manages this object
        struct soap *soap;
      public:
        /// Return unique type id SOAP_TYPE__ns1__qqCheckOnlineResponse
        virtual long soap_type(void) const { return SOAP_TYPE__ns1__qqCheckOnlineResponse; }
        /// (Re)set members to default values
        virtual void soap_default(struct soap*);
        /// Serialize object to prepare for SOAP 1.1/1.2 encoded output (or with SOAP_XML_GRAPH) by analyzing its (cyclic) structures
        virtual void soap_serialize(struct soap*) const;
        /// Output object in XML, compliant with SOAP 1.1 encoding style, return error code or SOAP_OK
        virtual int soap_put(struct soap*, const char *tag, const char *type) const;
        /// Output object in XML, with tag and optional id attribute and xsi:type, return error code or SOAP_OK
        virtual int soap_out(struct soap*, const char *tag, int id, const char *type) const;
        /// Get object from XML, compliant with SOAP 1.1 encoding style, return pointer to object or NULL on error
        virtual void *soap_get(struct soap*, const char *tag, const char *type);
        /// Get object from XML, with matching tag and type (NULL matches any tag and type), return pointer to object or NULL on error
        virtual void *soap_in(struct soap*, const char *tag, const char *type);
        /// Return a new object of type _ns1__qqCheckOnlineResponse, default initialized and not managed by a soap context
        virtual _ns1__qqCheckOnlineResponse *soap_alloc(void) const { return SOAP_NEW_UNMANAGED(_ns1__qqCheckOnlineResponse); }
      public:
        /// Constructor with default initializations
        _ns1__qqCheckOnlineResponse() : qqCheckOnlineResult(), soap() { }
        virtual ~_ns1__qqCheckOnlineResponse() { }
        /// Friend allocator used by soap_new__ns1__qqCheckOnlineResponse(struct soap*, int)
        friend SOAP_FMAC1 _ns1__qqCheckOnlineResponse * SOAP_FMAC2 soap_instantiate__ns1__qqCheckOnlineResponse(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* WeatherService.h:396 */
#ifndef SOAP_TYPE___ns1__qqCheckOnline
#define SOAP_TYPE___ns1__qqCheckOnline (16)
/* Wrapper: */
struct SOAP_CMAC __ns1__qqCheckOnline {
      public:
        /** Optional element 'ns1:qqCheckOnline' of XML schema type 'ns1:qqCheckOnline' */
        _ns1__qqCheckOnline *ns1__qqCheckOnline;
      public:
        /** Return unique type id SOAP_TYPE___ns1__qqCheckOnline */
        long soap_type() const { return SOAP_TYPE___ns1__qqCheckOnline; }
        /** Constructor with member initializations */
        __ns1__qqCheckOnline() : ns1__qqCheckOnline() { }
        /** Friend allocator */
        friend SOAP_FMAC1 __ns1__qqCheckOnline * SOAP_FMAC2 soap_instantiate___ns1__qqCheckOnline(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* WeatherService.h:469 */
#ifndef SOAP_TYPE___ns1__qqCheckOnline_
#define SOAP_TYPE___ns1__qqCheckOnline_ (18)
/* Wrapper: */
struct SOAP_CMAC __ns1__qqCheckOnline_ {
      public:
        /** Optional element 'ns1:qqCheckOnline' of XML schema type 'ns1:qqCheckOnline' */
        _ns1__qqCheckOnline *ns1__qqCheckOnline;
      public:
        /** Return unique type id SOAP_TYPE___ns1__qqCheckOnline_ */
        long soap_type() const { return SOAP_TYPE___ns1__qqCheckOnline_; }
        /** Constructor with member initializations */
        __ns1__qqCheckOnline_() : ns1__qqCheckOnline() { }
        /** Friend allocator */
        friend SOAP_FMAC1 __ns1__qqCheckOnline_ * SOAP_FMAC2 soap_instantiate___ns1__qqCheckOnline_(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* WeatherService.h:562 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (19)
/* SOAP_ENV__Header: */
struct SOAP_CMAC SOAP_ENV__Header {
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Header */
        long soap_type() const { return SOAP_TYPE_SOAP_ENV__Header; }
        /** Constructor with member initializations */
        SOAP_ENV__Header() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Header * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Header(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* WeatherService.h:562 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (20)
/* Type SOAP_ENV__Code is a recursive data type, (in)directly referencing itself through its (base or derived class) members */
/* SOAP_ENV__Code: */
struct SOAP_CMAC SOAP_ENV__Code {
      public:
        /** Optional element 'SOAP-ENV:Value' of XML schema type 'xsd:QName' */
        char *SOAP_ENV__Value;
        /** Optional element 'SOAP-ENV:Subcode' of XML schema type 'SOAP-ENV:Code' */
        struct SOAP_ENV__Code *SOAP_ENV__Subcode;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Code */
        long soap_type() const { return SOAP_TYPE_SOAP_ENV__Code; }
        /** Constructor with member initializations */
        SOAP_ENV__Code() : SOAP_ENV__Value(), SOAP_ENV__Subcode() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Code * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Code(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* WeatherService.h:562 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (22)
/* SOAP_ENV__Detail: */
struct SOAP_CMAC SOAP_ENV__Detail {
      public:
        char *__any;
        /** Any type of element 'fault' assigned to fault with its SOAP_TYPE_<typename> assigned to __type */
        /** Do not create a cyclic data structure throught this member unless SOAP encoding or SOAP_XML_GRAPH are used for id-ref serialization */
        int __type;
        void *fault;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Detail */
        long soap_type() const { return SOAP_TYPE_SOAP_ENV__Detail; }
        /** Constructor with member initializations */
        SOAP_ENV__Detail() : __any(), __type(), fault() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Detail * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Detail(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* WeatherService.h:562 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (25)
/* SOAP_ENV__Reason: */
struct SOAP_CMAC SOAP_ENV__Reason {
      public:
        /** Optional element 'SOAP-ENV:Text' of XML schema type 'xsd:string' */
        char *SOAP_ENV__Text;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Reason */
        long soap_type() const { return SOAP_TYPE_SOAP_ENV__Reason; }
        /** Constructor with member initializations */
        SOAP_ENV__Reason() : SOAP_ENV__Text() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Reason * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Reason(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/* WeatherService.h:562 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (26)
/* SOAP_ENV__Fault: */
struct SOAP_CMAC SOAP_ENV__Fault {
      public:
        /** Optional element 'faultcode' of XML schema type 'xsd:QName' */
        char *faultcode;
        /** Optional element 'faultstring' of XML schema type 'xsd:string' */
        char *faultstring;
        /** Optional element 'faultactor' of XML schema type 'xsd:string' */
        char *faultactor;
        /** Optional element 'detail' of XML schema type 'SOAP-ENV:Detail' */
        struct SOAP_ENV__Detail *detail;
        /** Optional element 'SOAP-ENV:Code' of XML schema type 'SOAP-ENV:Code' */
        struct SOAP_ENV__Code *SOAP_ENV__Code;
        /** Optional element 'SOAP-ENV:Reason' of XML schema type 'SOAP-ENV:Reason' */
        struct SOAP_ENV__Reason *SOAP_ENV__Reason;
        /** Optional element 'SOAP-ENV:Node' of XML schema type 'xsd:string' */
        char *SOAP_ENV__Node;
        /** Optional element 'SOAP-ENV:Role' of XML schema type 'xsd:string' */
        char *SOAP_ENV__Role;
        /** Optional element 'SOAP-ENV:Detail' of XML schema type 'SOAP-ENV:Detail' */
        struct SOAP_ENV__Detail *SOAP_ENV__Detail;
      public:
        /** Return unique type id SOAP_TYPE_SOAP_ENV__Fault */
        long soap_type() const { return SOAP_TYPE_SOAP_ENV__Fault; }
        /** Constructor with member initializations */
        SOAP_ENV__Fault() : faultcode(), faultstring(), faultactor(), detail(), SOAP_ENV__Code(), SOAP_ENV__Reason(), SOAP_ENV__Node(), SOAP_ENV__Role(), SOAP_ENV__Detail() { }
        /** Friend allocator */
        friend SOAP_FMAC1 SOAP_ENV__Fault * SOAP_FMAC2 soap_instantiate_SOAP_ENV__Fault(struct soap*, int, const char*, const char*, size_t*);
};
#endif
#endif

/******************************************************************************\
 *                                                                            *
 * Typedefs                                                                   *
 *                                                                            *
\******************************************************************************/


/* (built-in):0 */
#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (5)
typedef char *_XML;
#endif

/* (built-in):0 */
#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (6)
typedef char *_QName;
#endif

/******************************************************************************\
 *                                                                            *
 * Serializable Types                                                         *
 *                                                                            *
\******************************************************************************/


/* char has binding name 'byte' for type 'xsd:byte' */
#ifndef SOAP_TYPE_byte
#define SOAP_TYPE_byte (3)
#endif

/* int has binding name 'int' for type 'xsd:int' */
#ifndef SOAP_TYPE_int
#define SOAP_TYPE_int (1)
#endif

/* std::string has binding name 'std__string' for type 'xsd:string' */
#ifndef SOAP_TYPE_std__string
#define SOAP_TYPE_std__string (10)
#endif

/* _ns1__qqCheckOnlineResponse has binding name '_ns1__qqCheckOnlineResponse' for type '' */
#ifndef SOAP_TYPE__ns1__qqCheckOnlineResponse
#define SOAP_TYPE__ns1__qqCheckOnlineResponse (9)
#endif

/* _ns1__qqCheckOnline has binding name '_ns1__qqCheckOnline' for type '' */
#ifndef SOAP_TYPE__ns1__qqCheckOnline
#define SOAP_TYPE__ns1__qqCheckOnline (8)
#endif

/* struct SOAP_ENV__Fault has binding name 'SOAP_ENV__Fault' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (26)
#endif

/* struct SOAP_ENV__Reason has binding name 'SOAP_ENV__Reason' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (25)
#endif

/* struct SOAP_ENV__Detail has binding name 'SOAP_ENV__Detail' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (22)
#endif

/* struct SOAP_ENV__Code has binding name 'SOAP_ENV__Code' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (20)
#endif

/* struct SOAP_ENV__Header has binding name 'SOAP_ENV__Header' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (19)
#endif

/* struct SOAP_ENV__Reason * has binding name 'PointerToSOAP_ENV__Reason' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason
#define SOAP_TYPE_PointerToSOAP_ENV__Reason (28)
#endif

/* struct SOAP_ENV__Detail * has binding name 'PointerToSOAP_ENV__Detail' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail
#define SOAP_TYPE_PointerToSOAP_ENV__Detail (27)
#endif

/* struct SOAP_ENV__Code * has binding name 'PointerToSOAP_ENV__Code' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code
#define SOAP_TYPE_PointerToSOAP_ENV__Code (21)
#endif

/* _ns1__qqCheckOnline * has binding name 'PointerTo_ns1__qqCheckOnline' for type '' */
#ifndef SOAP_TYPE_PointerTo_ns1__qqCheckOnline
#define SOAP_TYPE_PointerTo_ns1__qqCheckOnline (13)
#endif

/* std::string * has binding name 'PointerTostd__string' for type 'xsd:string' */
#ifndef SOAP_TYPE_PointerTostd__string
#define SOAP_TYPE_PointerTostd__string (11)
#endif

/* _QName has binding name '_QName' for type 'xsd:QName' */
#ifndef SOAP_TYPE__QName
#define SOAP_TYPE__QName (6)
#endif

/* _XML has binding name '_XML' for type '' */
#ifndef SOAP_TYPE__XML
#define SOAP_TYPE__XML (5)
#endif

/* char * has binding name 'string' for type 'xsd:string' */
#ifndef SOAP_TYPE_string
#define SOAP_TYPE_string (4)
#endif

/******************************************************************************\
 *                                                                            *
 * Externals                                                                  *
 *                                                                            *
\******************************************************************************/


/******************************************************************************\
 *                                                                            *
 * Client-Side Call Stub Functions                                            *
 *                                                                            *
\******************************************************************************/

    
    /** Web service synchronous operation 'soap_call___ns1__qqCheckOnline' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__qqCheckOnline(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__qqCheckOnline *ns1__qqCheckOnline, _ns1__qqCheckOnlineResponse &ns1__qqCheckOnlineResponse);
    /** Web service asynchronous operation 'soap_send___ns1__qqCheckOnline' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_send___ns1__qqCheckOnline(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__qqCheckOnline *ns1__qqCheckOnline);
    /** Web service asynchronous operation 'soap_recv___ns1__qqCheckOnline' to receive a response message from the connected endpoint, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_recv___ns1__qqCheckOnline(struct soap *soap, _ns1__qqCheckOnlineResponse &ns1__qqCheckOnlineResponse);
    
    /** Web service synchronous operation 'soap_call___ns1__qqCheckOnline_' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__qqCheckOnline_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__qqCheckOnline *ns1__qqCheckOnline, _ns1__qqCheckOnlineResponse &ns1__qqCheckOnlineResponse);
    /** Web service asynchronous operation 'soap_send___ns1__qqCheckOnline_' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_send___ns1__qqCheckOnline_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__qqCheckOnline *ns1__qqCheckOnline);
    /** Web service asynchronous operation 'soap_recv___ns1__qqCheckOnline_' to receive a response message from the connected endpoint, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_recv___ns1__qqCheckOnline_(struct soap *soap, _ns1__qqCheckOnlineResponse &ns1__qqCheckOnlineResponse);

/******************************************************************************\
 *                                                                            *
 * Server-Side Operations                                                     *
 *                                                                            *
\******************************************************************************/

    /** Web service operation '__ns1__qqCheckOnline' implementation, should return SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 __ns1__qqCheckOnline(struct soap*, _ns1__qqCheckOnline *ns1__qqCheckOnline, _ns1__qqCheckOnlineResponse &ns1__qqCheckOnlineResponse);
    /** Web service operation '__ns1__qqCheckOnline_' implementation, should return SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 __ns1__qqCheckOnline_(struct soap*, _ns1__qqCheckOnline *ns1__qqCheckOnline, _ns1__qqCheckOnlineResponse &ns1__qqCheckOnlineResponse);

/******************************************************************************\
 *                                                                            *
 * Server-Side Skeletons to Invoke Service Operations                         *
 *                                                                            *
\******************************************************************************/

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve(struct soap*);

extern "C" SOAP_FMAC5 int SOAP_FMAC6 soap_serve_request(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___ns1__qqCheckOnline(struct soap*);

SOAP_FMAC5 int SOAP_FMAC6 soap_serve___ns1__qqCheckOnline_(struct soap*);

#endif

/* End of soapStub.h */