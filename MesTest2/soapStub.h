/* soapStub.h
   Generated by gSOAP 2.8.84 for MesWebservice.h

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
#define SOAP_NAMESPACE_OF_ns1	"http://tempuri.org/"

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

class _ns1__BarCodeSend;	/* MesWebservice.h:151 */
class _ns1__BarCodeSendResponse;	/* MesWebservice.h:153 */
class _ns1__BarCodeTable;	/* MesWebservice.h:155 */
class _ns1__BarCodeTableResponse_BarCodeTableResult;	/* MesWebservice.h:270 */
class _ns1__BarCodeTableResponse;	/* MesWebservice.h:157 */
class _ns1__DataTable;	/* MesWebservice.h:159 */
struct __ns1__BarCodeSend;	/* MesWebservice.h:480 */
struct __ns1__BarCodeTable;	/* MesWebservice.h:550 */
struct __ns1__BarCodeSend_;	/* MesWebservice.h:620 */
struct __ns1__BarCodeTable_;	/* MesWebservice.h:690 */

/* MesWebservice.h:151 */
#ifndef SOAP_TYPE__ns1__BarCodeSend
#define SOAP_TYPE__ns1__BarCodeSend (8)
/* complex XML schema type 'ns1:BarCodeSend': */
class SOAP_CMAC _ns1__BarCodeSend {
      public:
        /// Optional element 'ns1:barcode' of XML schema type 'xsd:string'
        std::string *barcode;
        /// Context that manages this object
        struct soap *soap;
      public:
        /// Return unique type id SOAP_TYPE__ns1__BarCodeSend
        virtual long soap_type(void) const { return SOAP_TYPE__ns1__BarCodeSend; }
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
        /// Return a new object of type _ns1__BarCodeSend, default initialized and not managed by a soap context
        virtual _ns1__BarCodeSend *soap_alloc(void) const { return SOAP_NEW_UNMANAGED(_ns1__BarCodeSend); }
      public:
        /// Constructor with default initializations
        _ns1__BarCodeSend() : barcode(), soap() { }
        virtual ~_ns1__BarCodeSend() { }
        /// Friend allocator used by soap_new__ns1__BarCodeSend(struct soap*, int)
        friend SOAP_FMAC1 _ns1__BarCodeSend * SOAP_FMAC2 soap_instantiate__ns1__BarCodeSend(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:153 */
#ifndef SOAP_TYPE__ns1__BarCodeSendResponse
#define SOAP_TYPE__ns1__BarCodeSendResponse (9)
/* complex XML schema type 'ns1:BarCodeSendResponse': */
class SOAP_CMAC _ns1__BarCodeSendResponse {
      public:
        /// Optional element 'ns1:BarCodeSendResult' of XML schema type 'xsd:string'
        std::string *BarCodeSendResult;
        /// Context that manages this object
        struct soap *soap;
      public:
        /// Return unique type id SOAP_TYPE__ns1__BarCodeSendResponse
        virtual long soap_type(void) const { return SOAP_TYPE__ns1__BarCodeSendResponse; }
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
        /// Return a new object of type _ns1__BarCodeSendResponse, default initialized and not managed by a soap context
        virtual _ns1__BarCodeSendResponse *soap_alloc(void) const { return SOAP_NEW_UNMANAGED(_ns1__BarCodeSendResponse); }
      public:
        /// Constructor with default initializations
        _ns1__BarCodeSendResponse() : BarCodeSendResult(), soap() { }
        virtual ~_ns1__BarCodeSendResponse() { }
        /// Friend allocator used by soap_new__ns1__BarCodeSendResponse(struct soap*, int)
        friend SOAP_FMAC1 _ns1__BarCodeSendResponse * SOAP_FMAC2 soap_instantiate__ns1__BarCodeSendResponse(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:155 */
#ifndef SOAP_TYPE__ns1__BarCodeTable
#define SOAP_TYPE__ns1__BarCodeTable (10)
/* complex XML schema type 'ns1:BarCodeTable': */
class SOAP_CMAC _ns1__BarCodeTable {
      public:
        /// Optional element 'ns1:barcode' of XML schema type 'xsd:string'
        std::string *barcode;
        /// Context that manages this object
        struct soap *soap;
      public:
        /// Return unique type id SOAP_TYPE__ns1__BarCodeTable
        virtual long soap_type(void) const { return SOAP_TYPE__ns1__BarCodeTable; }
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
        /// Return a new object of type _ns1__BarCodeTable, default initialized and not managed by a soap context
        virtual _ns1__BarCodeTable *soap_alloc(void) const { return SOAP_NEW_UNMANAGED(_ns1__BarCodeTable); }
      public:
        /// Constructor with default initializations
        _ns1__BarCodeTable() : barcode(), soap() { }
        virtual ~_ns1__BarCodeTable() { }
        /// Friend allocator used by soap_new__ns1__BarCodeTable(struct soap*, int)
        friend SOAP_FMAC1 _ns1__BarCodeTable * SOAP_FMAC2 soap_instantiate__ns1__BarCodeTable(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:270 */
#ifndef SOAP_TYPE__ns1__BarCodeTableResponse_BarCodeTableResult
#define SOAP_TYPE__ns1__BarCodeTableResponse_BarCodeTableResult (16)
/* complex XML schema type 'ns1:BarCodeTableResponse-BarCodeTableResult': */
class SOAP_CMAC _ns1__BarCodeTableResponse_BarCodeTableResult {
      public:
        std::vector<char *> __any;
        char *__any_;
      public:
        /// Return unique type id SOAP_TYPE__ns1__BarCodeTableResponse_BarCodeTableResult
        virtual long soap_type(void) const { return SOAP_TYPE__ns1__BarCodeTableResponse_BarCodeTableResult; }
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
        /// Return a new object of type _ns1__BarCodeTableResponse_BarCodeTableResult, default initialized and not managed by a soap context
        virtual _ns1__BarCodeTableResponse_BarCodeTableResult *soap_alloc(void) const { return SOAP_NEW_UNMANAGED(_ns1__BarCodeTableResponse_BarCodeTableResult); }
      public:
        /// Constructor with default initializations
        _ns1__BarCodeTableResponse_BarCodeTableResult() : __any(), __any_() { }
        virtual ~_ns1__BarCodeTableResponse_BarCodeTableResult() { }
        /// Friend allocator used by soap_new__ns1__BarCodeTableResponse_BarCodeTableResult(struct soap*, int)
        friend SOAP_FMAC1 _ns1__BarCodeTableResponse_BarCodeTableResult * SOAP_FMAC2 soap_instantiate__ns1__BarCodeTableResponse_BarCodeTableResult(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:157 */
#ifndef SOAP_TYPE__ns1__BarCodeTableResponse
#define SOAP_TYPE__ns1__BarCodeTableResponse (11)
/* complex XML schema type 'ns1:BarCodeTableResponse': */
class SOAP_CMAC _ns1__BarCodeTableResponse {
      public:
        /// Optional element 'ns1:BarCodeTableResult' of XML schema type 'ns1:BarCodeTableResponse-BarCodeTableResult'
        _ns1__BarCodeTableResponse_BarCodeTableResult *BarCodeTableResult;
        /// Context that manages this object
        struct soap *soap;
      public:
        /// Return unique type id SOAP_TYPE__ns1__BarCodeTableResponse
        virtual long soap_type(void) const { return SOAP_TYPE__ns1__BarCodeTableResponse; }
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
        /// Return a new object of type _ns1__BarCodeTableResponse, default initialized and not managed by a soap context
        virtual _ns1__BarCodeTableResponse *soap_alloc(void) const { return SOAP_NEW_UNMANAGED(_ns1__BarCodeTableResponse); }
      public:
        /// Constructor with default initializations
        _ns1__BarCodeTableResponse() : BarCodeTableResult(), soap() { }
        virtual ~_ns1__BarCodeTableResponse() { }
        /// Friend allocator used by soap_new__ns1__BarCodeTableResponse(struct soap*, int)
        friend SOAP_FMAC1 _ns1__BarCodeTableResponse * SOAP_FMAC2 soap_instantiate__ns1__BarCodeTableResponse(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:159 */
#ifndef SOAP_TYPE__ns1__DataTable
#define SOAP_TYPE__ns1__DataTable (12)
/* complex XML schema type 'ns1:DataTable': */
class SOAP_CMAC _ns1__DataTable {
      public:
        std::vector<char *> __any;
        char *__any_;
        /// Context that manages this object
        struct soap *soap;
      public:
        /// Return unique type id SOAP_TYPE__ns1__DataTable
        virtual long soap_type(void) const { return SOAP_TYPE__ns1__DataTable; }
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
        /// Return a new object of type _ns1__DataTable, default initialized and not managed by a soap context
        virtual _ns1__DataTable *soap_alloc(void) const { return SOAP_NEW_UNMANAGED(_ns1__DataTable); }
      public:
        /// Constructor with default initializations
        _ns1__DataTable() : __any(), __any_(), soap() { }
        virtual ~_ns1__DataTable() { }
        /// Friend allocator used by soap_new__ns1__DataTable(struct soap*, int)
        friend SOAP_FMAC1 _ns1__DataTable * SOAP_FMAC2 soap_instantiate__ns1__DataTable(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:480 */
#ifndef SOAP_TYPE___ns1__BarCodeSend
#define SOAP_TYPE___ns1__BarCodeSend (22)
/* Wrapper: */
struct SOAP_CMAC __ns1__BarCodeSend {
      public:
        /** Optional element 'ns1:BarCodeSend' of XML schema type 'ns1:BarCodeSend' */
        _ns1__BarCodeSend *ns1__BarCodeSend;
      public:
        /** Return unique type id SOAP_TYPE___ns1__BarCodeSend */
        long soap_type() const { return SOAP_TYPE___ns1__BarCodeSend; }
        /** Constructor with member initializations */
        __ns1__BarCodeSend() : ns1__BarCodeSend() { }
        /** Friend allocator */
        friend SOAP_FMAC1 __ns1__BarCodeSend * SOAP_FMAC2 soap_instantiate___ns1__BarCodeSend(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:550 */
#ifndef SOAP_TYPE___ns1__BarCodeTable
#define SOAP_TYPE___ns1__BarCodeTable (26)
/* Wrapper: */
struct SOAP_CMAC __ns1__BarCodeTable {
      public:
        /** Optional element 'ns1:BarCodeTable' of XML schema type 'ns1:BarCodeTable' */
        _ns1__BarCodeTable *ns1__BarCodeTable;
      public:
        /** Return unique type id SOAP_TYPE___ns1__BarCodeTable */
        long soap_type() const { return SOAP_TYPE___ns1__BarCodeTable; }
        /** Constructor with member initializations */
        __ns1__BarCodeTable() : ns1__BarCodeTable() { }
        /** Friend allocator */
        friend SOAP_FMAC1 __ns1__BarCodeTable * SOAP_FMAC2 soap_instantiate___ns1__BarCodeTable(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:620 */
#ifndef SOAP_TYPE___ns1__BarCodeSend_
#define SOAP_TYPE___ns1__BarCodeSend_ (28)
/* Wrapper: */
struct SOAP_CMAC __ns1__BarCodeSend_ {
      public:
        /** Optional element 'ns1:BarCodeSend' of XML schema type 'ns1:BarCodeSend' */
        _ns1__BarCodeSend *ns1__BarCodeSend;
      public:
        /** Return unique type id SOAP_TYPE___ns1__BarCodeSend_ */
        long soap_type() const { return SOAP_TYPE___ns1__BarCodeSend_; }
        /** Constructor with member initializations */
        __ns1__BarCodeSend_() : ns1__BarCodeSend() { }
        /** Friend allocator */
        friend SOAP_FMAC1 __ns1__BarCodeSend_ * SOAP_FMAC2 soap_instantiate___ns1__BarCodeSend_(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:690 */
#ifndef SOAP_TYPE___ns1__BarCodeTable_
#define SOAP_TYPE___ns1__BarCodeTable_ (30)
/* Wrapper: */
struct SOAP_CMAC __ns1__BarCodeTable_ {
      public:
        /** Optional element 'ns1:BarCodeTable' of XML schema type 'ns1:BarCodeTable' */
        _ns1__BarCodeTable *ns1__BarCodeTable;
      public:
        /** Return unique type id SOAP_TYPE___ns1__BarCodeTable_ */
        long soap_type() const { return SOAP_TYPE___ns1__BarCodeTable_; }
        /** Constructor with member initializations */
        __ns1__BarCodeTable_() : ns1__BarCodeTable() { }
        /** Friend allocator */
        friend SOAP_FMAC1 __ns1__BarCodeTable_ * SOAP_FMAC2 soap_instantiate___ns1__BarCodeTable_(struct soap*, int, const char*, const char*, size_t*);
};
#endif

/* MesWebservice.h:828 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (31)
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

/* MesWebservice.h:828 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (32)
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

/* MesWebservice.h:828 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (34)
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

/* MesWebservice.h:828 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (37)
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

/* MesWebservice.h:828 */
#ifndef WITH_NOGLOBAL
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (38)
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

/* _ns1__BarCodeTableResponse_BarCodeTableResult has binding name '_ns1__BarCodeTableResponse_BarCodeTableResult' for type '' */
#ifndef SOAP_TYPE__ns1__BarCodeTableResponse_BarCodeTableResult
#define SOAP_TYPE__ns1__BarCodeTableResponse_BarCodeTableResult (16)
#endif

/* std::string has binding name 'std__string' for type 'xsd:string' */
#ifndef SOAP_TYPE_std__string
#define SOAP_TYPE_std__string (13)
#endif

/* _ns1__DataTable has binding name '_ns1__DataTable' for type '' */
#ifndef SOAP_TYPE__ns1__DataTable
#define SOAP_TYPE__ns1__DataTable (12)
#endif

/* _ns1__BarCodeTableResponse has binding name '_ns1__BarCodeTableResponse' for type '' */
#ifndef SOAP_TYPE__ns1__BarCodeTableResponse
#define SOAP_TYPE__ns1__BarCodeTableResponse (11)
#endif

/* _ns1__BarCodeTable has binding name '_ns1__BarCodeTable' for type '' */
#ifndef SOAP_TYPE__ns1__BarCodeTable
#define SOAP_TYPE__ns1__BarCodeTable (10)
#endif

/* _ns1__BarCodeSendResponse has binding name '_ns1__BarCodeSendResponse' for type '' */
#ifndef SOAP_TYPE__ns1__BarCodeSendResponse
#define SOAP_TYPE__ns1__BarCodeSendResponse (9)
#endif

/* _ns1__BarCodeSend has binding name '_ns1__BarCodeSend' for type '' */
#ifndef SOAP_TYPE__ns1__BarCodeSend
#define SOAP_TYPE__ns1__BarCodeSend (8)
#endif

/* struct SOAP_ENV__Fault has binding name 'SOAP_ENV__Fault' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Fault
#define SOAP_TYPE_SOAP_ENV__Fault (38)
#endif

/* struct SOAP_ENV__Reason has binding name 'SOAP_ENV__Reason' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Reason
#define SOAP_TYPE_SOAP_ENV__Reason (37)
#endif

/* struct SOAP_ENV__Detail has binding name 'SOAP_ENV__Detail' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Detail
#define SOAP_TYPE_SOAP_ENV__Detail (34)
#endif

/* struct SOAP_ENV__Code has binding name 'SOAP_ENV__Code' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Code
#define SOAP_TYPE_SOAP_ENV__Code (32)
#endif

/* struct SOAP_ENV__Header has binding name 'SOAP_ENV__Header' for type '' */
#ifndef SOAP_TYPE_SOAP_ENV__Header
#define SOAP_TYPE_SOAP_ENV__Header (31)
#endif

/* struct SOAP_ENV__Reason * has binding name 'PointerToSOAP_ENV__Reason' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Reason
#define SOAP_TYPE_PointerToSOAP_ENV__Reason (40)
#endif

/* struct SOAP_ENV__Detail * has binding name 'PointerToSOAP_ENV__Detail' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Detail
#define SOAP_TYPE_PointerToSOAP_ENV__Detail (39)
#endif

/* struct SOAP_ENV__Code * has binding name 'PointerToSOAP_ENV__Code' for type '' */
#ifndef SOAP_TYPE_PointerToSOAP_ENV__Code
#define SOAP_TYPE_PointerToSOAP_ENV__Code (33)
#endif

/* _ns1__BarCodeTable * has binding name 'PointerTo_ns1__BarCodeTable' for type '' */
#ifndef SOAP_TYPE_PointerTo_ns1__BarCodeTable
#define SOAP_TYPE_PointerTo_ns1__BarCodeTable (23)
#endif

/* _ns1__BarCodeSend * has binding name 'PointerTo_ns1__BarCodeSend' for type '' */
#ifndef SOAP_TYPE_PointerTo_ns1__BarCodeSend
#define SOAP_TYPE_PointerTo_ns1__BarCodeSend (19)
#endif

/* _ns1__BarCodeTableResponse_BarCodeTableResult * has binding name 'PointerTo_ns1__BarCodeTableResponse_BarCodeTableResult' for type '' */
#ifndef SOAP_TYPE_PointerTo_ns1__BarCodeTableResponse_BarCodeTableResult
#define SOAP_TYPE_PointerTo_ns1__BarCodeTableResponse_BarCodeTableResult (18)
#endif

/* std::string * has binding name 'PointerTostd__string' for type 'xsd:string' */
#ifndef SOAP_TYPE_PointerTostd__string
#define SOAP_TYPE_PointerTostd__string (14)
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

/* std::vector<char *>  has binding name 'std__vectorTemplateOf_XML' for type '' */
#ifndef SOAP_TYPE_std__vectorTemplateOf_XML
#define SOAP_TYPE_std__vectorTemplateOf_XML (17)
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

    
    /** Web service synchronous operation 'soap_call___ns1__BarCodeSend' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__BarCodeSend(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__BarCodeSend *ns1__BarCodeSend, _ns1__BarCodeSendResponse &ns1__BarCodeSendResponse);
    /** Web service asynchronous operation 'soap_send___ns1__BarCodeSend' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_send___ns1__BarCodeSend(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__BarCodeSend *ns1__BarCodeSend);
    /** Web service asynchronous operation 'soap_recv___ns1__BarCodeSend' to receive a response message from the connected endpoint, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_recv___ns1__BarCodeSend(struct soap *soap, _ns1__BarCodeSendResponse &ns1__BarCodeSendResponse);
    
    /** Web service synchronous operation 'soap_call___ns1__BarCodeTable' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__BarCodeTable(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__BarCodeTable *ns1__BarCodeTable, _ns1__BarCodeTableResponse &ns1__BarCodeTableResponse);
    /** Web service asynchronous operation 'soap_send___ns1__BarCodeTable' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_send___ns1__BarCodeTable(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__BarCodeTable *ns1__BarCodeTable);
    /** Web service asynchronous operation 'soap_recv___ns1__BarCodeTable' to receive a response message from the connected endpoint, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_recv___ns1__BarCodeTable(struct soap *soap, _ns1__BarCodeTableResponse &ns1__BarCodeTableResponse);
    
    /** Web service synchronous operation 'soap_call___ns1__BarCodeSend_' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__BarCodeSend_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__BarCodeSend *ns1__BarCodeSend, _ns1__BarCodeSendResponse &ns1__BarCodeSendResponse);
    /** Web service asynchronous operation 'soap_send___ns1__BarCodeSend_' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_send___ns1__BarCodeSend_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__BarCodeSend *ns1__BarCodeSend);
    /** Web service asynchronous operation 'soap_recv___ns1__BarCodeSend_' to receive a response message from the connected endpoint, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_recv___ns1__BarCodeSend_(struct soap *soap, _ns1__BarCodeSendResponse &ns1__BarCodeSendResponse);
    
    /** Web service synchronous operation 'soap_call___ns1__BarCodeTable_' to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_call___ns1__BarCodeTable_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__BarCodeTable *ns1__BarCodeTable, _ns1__BarCodeTableResponse &ns1__BarCodeTableResponse);
    /** Web service asynchronous operation 'soap_send___ns1__BarCodeTable_' to send a request message to the specified endpoint and SOAP Action header, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_send___ns1__BarCodeTable_(struct soap *soap, const char *soap_endpoint, const char *soap_action, _ns1__BarCodeTable *ns1__BarCodeTable);
    /** Web service asynchronous operation 'soap_recv___ns1__BarCodeTable_' to receive a response message from the connected endpoint, returns SOAP_OK or error code */
    SOAP_FMAC5 int SOAP_FMAC6 soap_recv___ns1__BarCodeTable_(struct soap *soap, _ns1__BarCodeTableResponse &ns1__BarCodeTableResponse);

#endif

/* End of soapStub.h */
