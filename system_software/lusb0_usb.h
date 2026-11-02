#ifndef __USB_H__
#define __USB_H__

#include <stdlib.h>
#include <windows.h>

/*
 * 'interface' is defined somewhere in the Windows header files. This macro
 * is deleted here to avoid conflicts and compile errors.
 */

#ifdef interface
#undef interface
#endif

/*
 * PATH_MAX from limits.h can't be used on Windows if the dll and
 * import libraries are build/used by different compilers
 */

#define LIBUSB_PATH_MAX 512


/*
 * USB spec information
 *
 * This is all stuff grabbed from various USB specs and is pretty much
 * not topic to change
 */

/*
 * Device and/or Interface Class codes
 */
#define USB_CLASS_PER_INTERFACE		0	/* for DeviceClass */
#define USB_CLASS_AUDIO			      1
#define USB_CLASS_COMM			      2
#define USB_CLASS_HID			        3
#define USB_CLASS_PRINTER		      7
#define USB_CLASS_MASS_STORAGE		8
#define USB_CLASS_HUB			        9
#define USB_CLASS_DATA			      10
#define USB_CLASS_VENDOR_SPEC		  0xff

/*
 * Descriptor types
 */
#define USB_DT_DEVICE			0x01
#define USB_DT_CONFIG			0x02
#define USB_DT_STRING			0x03
#define USB_DT_INTERFACE	0x04
#define USB_DT_ENDPOINT		0x05

#define USB_DT_HID			0x21
#define USB_DT_REPORT		0x22
#define USB_DT_PHYSICAL	0x23
#define USB_DT_HUB			0x29

/*
 * Descriptor sizes per descriptor type
 */
#define USB_DT_DEVICE_SIZE		18
#define USB_DT_CONFIG_SIZE		9
#define USB_DT_INTERFACE_SIZE		9
#define USB_DT_ENDPOINT_SIZE		7
#define USB_DT_ENDPOINT_AUDIO_SIZE	9	/* Audio extension */
#define USB_DT_HUB_NONVAR_SIZE		7


/* ensure ::u8-packed structures */
#include <pshpack1.h>


/* All standard descriptors have these 2 fields in common */
struct usb_descriptor_header
{
    ::u8  bLength;
    ::u8  bDescriptorType;
};

/* String descriptor */
struct usb_string_descriptor
{
    ::u8  bLength;
    ::u8  bDescriptorType;
    ::u16 wData[1];
};

/* HID descriptor */
struct usb_hid_descriptor
{
    ::u8  bLength;
    ::u8  bDescriptorType;
    ::u16 bcdHID;
    ::u8  bCountryCode;
    ::u8  bNumDescriptors;
};

/* Endpoint descriptor */
#define USB_MAXENDPOINTS	32
struct usb_endpoint_descriptor
{
    ::u8  bLength;
    ::u8  bDescriptorType;
    ::u8  bEndpointAddress;
    ::u8  bmAttributes;
    ::u16 wMaxPacketSize;
    ::u8  bInterval;
    ::u8  bRefresh;
    ::u8  bSynchAddress;

    ::u8 *extra;	/* Extra descriptors */
    ::i32 extralen;
};

#define USB_ENDPOINT_ADDRESS_MASK	0x0f    /* in bEndpointAddress */
#define USB_ENDPOINT_DIR_MASK		  0x80

#define USB_ENDPOINT_TYPE_MASK		0x03    /* in bmAttributes */
#define USB_ENDPOINT_TYPE_CONTROL	    0
#define USB_ENDPOINT_TYPE_ISOCHRONOUS	1
#define USB_ENDPOINT_TYPE_BULK		    2
#define USB_ENDPOINT_TYPE_INTERRUPT	  3

/* Interface descriptor */
#define USB_MAXINTERFACES	32
struct usb_interface_descriptor
{
    ::u8  bLength;
    ::u8  bDescriptorType;
    ::u8  bInterfaceNumber;
    ::u8  bAlternateSetting;
    ::u8  bNumEndpoints;
    ::u8  bInterfaceClass;
    ::u8  bInterfaceSubClass;
    ::u8  bInterfaceProtocol;
    ::u8  iInterface;

    struct usb_endpoint_descriptor *endpoint;

    ::u8 *extra;	/* Extra descriptors */
    ::i32 extralen;
};

#define USB_MAXALTSETTING	128	/* Hard limit */

struct usb_interface
{
    struct usb_interface_descriptor *altsetting;

    ::i32 num_altsetting;
};

/* Configuration descriptor information.. */
#define USB_MAXCONFIG		8
struct usb_config_descriptor
{
    ::u8  bLength;
    ::u8  bDescriptorType;
    ::u16 wTotalLength;
    ::u8  bNumInterfaces;
    ::u8  bConfigurationValue;
    ::u8  iConfiguration;
    ::u8  bmAttributes;
    ::u8  MaxPower;

    struct usb_interface *interface;

    ::u8 *extra;	/* Extra descriptors */
    ::i32 extralen;
};

/* Device descriptor */
struct usb_device_descriptor
{
    ::u8  bLength;
    ::u8  bDescriptorType;
    ::u16 bcdUSB;
    ::u8  bDeviceClass;
    ::u8  bDeviceSubClass;
    ::u8  bDeviceProtocol;
    ::u8  bMaxPacketSize0;
    ::u16 idVendor;
    ::u16 idProduct;
    ::u16 bcdDevice;
    ::u8  iManufacturer;
    ::u8  iProduct;
    ::u8  iSerialNumber;
    ::u8  bNumConfigurations;
};

struct usb_ctrl_setup
{
    ::u8  bRequestType;
    ::u8  bRequest;
    ::u16 wValue;
    ::u16 wIndex;
    ::u16 wLength;
};

/*
 * Standard requests
 */
#define USB_REQ_GET_STATUS		    0x00
#define USB_REQ_CLEAR_FEATURE	    0x01
/* 0x02 is reserved */
#define USB_REQ_SET_FEATURE		    0x03
/* 0x04 is reserved */
#define USB_REQ_SET_ADDRESS		    0x05
#define USB_REQ_GET_DESCRIPTOR		0x06
#define USB_REQ_SET_DESCRIPTOR		0x07
#define USB_REQ_GET_CONFIGURATION	0x08
#define USB_REQ_SET_CONFIGURATION	0x09
#define USB_REQ_GET_INTERFACE		  0x0A
#define USB_REQ_SET_INTERFACE		  0x0B
#define USB_REQ_SYNCH_FRAME		    0x0C

#define USB_TYPE_STANDARD		(0x00 << 5)
#define USB_TYPE_CLASS			(0x01 << 5)
#define USB_TYPE_VENDOR			(0x02 << 5)
#define USB_TYPE_RESERVED		(0x03 << 5)

#define USB_RECIP_DEVICE		0x00
#define USB_RECIP_INTERFACE	0x01
#define USB_RECIP_ENDPOINT	0x02
#define USB_RECIP_OTHER			0x03

/*
 * Various libusb API related stuff
 */

#define USB_ENDPOINT_IN			0x80
#define USB_ENDPOINT_OUT		0x00

/* Error codes */
#define USB_ERROR_BEGIN			500000

/*
 * This is supposed to look weird. This file is generated from autoconf
 * and I didn't want to make this too complicated.
 */
#define USB_LE16_TO_CPU(x)

/*
 * Device reset types for usb_reset_ex.
 * http://msdn.microsoft.com/en-us/library/ff537269%28VS.85%29.aspx
 * http://msdn.microsoft.com/en-us/library/ff537243%28v=vs.85%29.aspx
 */
#define USB_RESET_TYPE_RESET_PORT (1 << 0)
#define USB_RESET_TYPE_CYCLE_PORT (1 << 1)
#define USB_RESET_TYPE_FULL_RESET (USB_RESET_TYPE_CYCLE_PORT | USB_RESET_TYPE_RESET_PORT)


/* Data types */
/* struct usb_device; */
/* struct usb_bus; */

struct usb_device
{
    struct usb_device *next, *prev;

    ::i8 filename[LIBUSB_PATH_MAX];

    struct usb_bus *bus;

    struct usb_device_descriptor descriptor;
    struct usb_config_descriptor *config;

    void *dev;		/* Darwin support */

    ::u8 devnum;

    ::u8 num_children;
    struct usb_device **children;
};

struct usb_bus
{
    struct usb_bus *next, *prev;

    ::i8 dirname[LIBUSB_PATH_MAX];

    struct usb_device *devices;
    unsigned long location;

    struct usb_device *root_dev;
};

/* Version information, Windows specific */
struct usb_version
{
    struct
    {
        ::i32 major;
        ::i32 minor;
        ::i32 micro;
        ::i32 nano;
    } dll;
    struct
    {
        ::i32 major;
        ::i32 minor;
        ::i32 micro;
        ::i32 nano;
    } driver;
};


struct usb_dev_handle;
typedef struct usb_dev_handle usb_dev_handle;

/* Variables */
#ifndef __USB_C__
#define usb_busses usb_get_busses()
#endif



#include <poppack.h>


#ifdef __cplusplus
extern "C"
{
#endif

    /* Function prototypes */

    /* usb.c */
    usb_dev_handle *usb_open(struct usb_device *dev);
    ::i32 usb_close(usb_dev_handle *dev);
    ::i32 usb_get_string(usb_dev_handle *dev, ::i32 index, ::i32 langid, ::i8 *buf,
                       size_t buflen);
    ::i32 usb_get_string_simple(usb_dev_handle *dev, ::i32 index, ::i8 *buf,
                              size_t buflen);

    /* descriptors.c */
    ::i32 usb_get_descriptor_by_endpoint(usb_dev_handle *udev, ::i32 ep,
                                       ::u8 type, ::u8 index,
                                       void *buf, ::i32 i32_size);
    ::i32 usb_get_descriptor(usb_dev_handle *udev, ::u8 type,
                           ::u8 index, void *buf, ::i32 i32_size);

    /* <arch>.c */
    ::i32 usb_bulk_write(usb_dev_handle *dev, ::i32 ep, ::i8 *bytes, ::i32 size,
                       ::i32 timeout);
    ::i32 usb_bulk_read(usb_dev_handle *dev, ::i32 ep, ::i8 *bytes, ::i32 size,
                      ::i32 timeout);
    ::i32 usb_interrupt_write(usb_dev_handle *dev, ::i32 ep, ::i8 *bytes, ::i32 size,
                            ::i32 timeout);
    ::i32 usb_interrupt_read(usb_dev_handle *dev, ::i32 ep, ::i8 *bytes, ::i32 size,
                           ::i32 timeout);
    ::i32 usb_control_msg(usb_dev_handle *dev, ::i32 requesttype, ::i32 request,
                        ::i32 value, ::i32 index, ::i8 *bytes, ::i32 size,
                        ::i32 timeout);
    ::i32 usb_set_configuration(usb_dev_handle *dev, ::i32 configuration);
    ::i32 usb_claim_interface(usb_dev_handle *dev, ::i32 interface);
    ::i32 usb_release_interface(usb_dev_handle *dev, ::i32 interface);
    ::i32 usb_set_altinterface(usb_dev_handle *dev, ::i32 alternate);
    ::i32 usb_resetep(usb_dev_handle *dev, ::u32 ep);
    ::i32 usb_clear_halt(usb_dev_handle *dev, ::u32 ep);
    ::i32 usb_reset(usb_dev_handle *dev);
    ::i32 usb_reset_ex(usb_dev_handle *dev, ::u32 reset_type);

    ::i8 *usb_strerror(void);

    void usb_init(void);
    void usb_set_debug(::i32 level);
    ::i32 usb_find_busses(void);
    ::i32 usb_find_devices(void);
    struct usb_device *usb_device(usb_dev_handle *dev);
    struct usb_bus *usb_get_busses(void);


    /* Windows specific functions */

#define LIBUSB_HAS_INSTALL_SERVICE_NP 1
    ::i32 usb_install_service_np(void);
    void CALLBACK usb_install_service_np_rundll(HWND wnd, HINSTANCE instance,
            LPSTR cmd_line, ::i32 cmd_show);

#define LIBUSB_HAS_UNINSTALL_SERVICE_NP 1
    ::i32 usb_uninstall_service_np(void);
    void CALLBACK usb_uninstall_service_np_rundll(HWND wnd, HINSTANCE instance,
            LPSTR cmd_line, ::i32 cmd_show);

#define LIBUSB_HAS_INSTALL_DRIVER_NP 1
    ::i32 usb_install_driver_np(const ::string &inf_file);
    void CALLBACK usb_install_driver_np_rundll(HWND wnd, HINSTANCE instance,
            LPSTR cmd_line, ::i32 cmd_show);

#define LIBUSB_HAS_TOUCH_INF_FILE_NP 1
    ::i32 usb_touch_inf_file_np(const ::string &inf_file);
    void CALLBACK usb_touch_inf_file_np_rundll(HWND wnd, HINSTANCE instance,
            LPSTR cmd_line, ::i32 cmd_show);

#define LIBUSB_HAS_INSTALL_NEEDS_RESTART_NP 1
    ::i32 usb_install_needs_restart_np(void);

#define LIBUSB_HAS_INSTALL_NP 1
    ::i32 usb_install_npW(HWND hwnd, HINSTANCE instance, LPCWSTR cmd_line, ::i32 starg_arg);
    ::i32 usb_install_npA(HWND hwnd, HINSTANCE instance, LPCSTR cmd_line, ::i32 starg_arg);
	#define usb_install_np usb_install_npA
    void CALLBACK usb_install_np_rundll(HWND wnd, HINSTANCE instance, 
            LPSTR cmd_line, ::i32 cmd_show);

    const struct usb_version *usb_get_version(void);

    ::i32 usb_isochronous_setup_async(usb_dev_handle *dev, void **action_context,
                                    ::u8 ep, ::i32 pktsize);
    ::i32 usb_bulk_setup_async(usb_dev_handle *dev, void **action_context,
                             ::u8 ep);
    ::i32 usb_interrupt_setup_async(usb_dev_handle *dev, void **action_context,
                                  ::u8 ep);

    ::i32 usb_submit_async(void *action_context, ::i8 *bytes, ::i32 i32_size);
    ::i32 usb_reap_async(void *action_context, ::i32 timeout);
    ::i32 usb_reap_async_nocancel(void *action_context, ::i32 timeout);
    ::i32 usb_cancel_async(void *action_context);
    ::i32 usb_free_async(void **action_context);


#ifdef __cplusplus
}
#endif

#endif /* __USB_H__ */

