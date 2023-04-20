// This file can be included several times.
// ^
// this is a hack because the ./scripts/check_header_guards.py
// script does not really support the rust files
#pragma once
#include <base/rust.h>

int str_width_unicode(const char *text) noexcept;