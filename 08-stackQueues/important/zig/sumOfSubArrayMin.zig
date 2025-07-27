const std = @import("std");
const Allocator = std.mem.Allocator;

fn Min(A: i32, B: i32) i32 {
    if (A < B) {
        return A;
    } else {
        return B;
    }
}

fn sum_of_sub_min_brute(arr: []i32) i32 {
    var sum: i32 = 0;
    const n = arr.len;
    for (0..n) |i| {
        var min: i32 = arr[i];
        for (i..n) |j| {
            min = Min(min, arr[j]);
            sum += min;
        }
    }
    return sum;
}

// pub fn main() !void {
//     var arr = [_]i32{ 3, 1, 2, 4 };
//     const sum = sum_of_sub_min_brute(arr[0..]);
//     std.debug.print("{d}", .{sum});
// }
