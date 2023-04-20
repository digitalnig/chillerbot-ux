use std::ffi::CStr;
use std::os::raw::c_char;

extern crate unicode_width;

use unicode_width::UnicodeWidthStr;

#[cxx::bridge]
mod ffi {
    extern "C++" {
        include!("base/rust.h");
    }
    extern "Rust" {
        unsafe fn str_width_unicode(text: *const c_char) -> i32;
    }
}

/// Count the width in columns of a given string.
///
/// So one can get the display length of any string
/// in a fixed width font scenario.
///
/// Simply calling str_length() does not work if there is unicode
/// since some unicode characters can be multiple bytes
/// and even counting unicode characters does not work
/// because CJK (chines/japan/korean) characters
/// have a concept of full and half width
/// meaning one single unicode character can span two columns
///
/// For example this character spans two columns
/// ```text
/// +--+
/// |困|
/// |12|
/// +--+
/// ```
#[allow(non_snake_case)]
pub fn str_width_unicode(text: *const c_char) -> i32 {
    let slice = unsafe { CStr::from_ptr(text) };
    let slice = slice.to_str().unwrap_or_default();
    // .width_cjk().try_into().unwrap();
    // returns width 2 for the letter é
    let width = UnicodeWidthStr::width(slice) as i32;
    return width;
}
