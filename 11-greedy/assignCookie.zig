const std = @import("std");

// Problem Statement: Consider a scenario where a teacher wants to distribute cookies to students,
//  with each student receiving at most one cookie. Given two arrays, student and cookie,
//  the ith value in the student array describes the minimum size of cookie
//  that the ith student can be assigned.The jth value in the cookie array represents
//  the size of the jth cookie. If cookie[j] >= student[i], the jth cookie can be assigned
//  to the ith student. Maximize the number of students assigned with cookies and output
//  the maximum number.

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
    _ = assignCookie(cookie[0..], greed[0..]);
}
