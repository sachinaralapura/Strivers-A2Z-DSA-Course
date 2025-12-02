const std = @import("std");

pub fn assignCookie(cookie: []usize, greed: []usize) usize {
    std.sort.heap(usize, cookie, {}, comptime std.sort.asc(usize));
    std.sort.heap(usize, greed, {}, comptime std.sort.asc(usize));
    const cookie_size = cookie.len;
    const greed_size = greed.len;
    var cookie_index: usize = 0;
    var greed_index: usize = 0;

    while (cookie_index < cookie_size and greed_index < greed_size) {
        if (greed[greed_index] <= cookie[cookie_index]) {
            greed_index += 1;
        }
        cookie_index += 1;
    }
    return greed_index;
}

pub fn main() !void {
    var cookie = [_]usize{ 4, 2, 1, 2, 1, 3 };
    var greed = [_]usize{ 1, 5, 3, 3, 4 };
    try assignCookie(cookie[0..], greed[0..]);
}
