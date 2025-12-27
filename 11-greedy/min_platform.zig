// Problem Statement: We are given two arrays that represent the arrival
//  and departure times of trains that stop at the platform. We need to find the minimum number
//  of platforms needed at the railway station so that no train has to wait.

const std = @import("std");
const Sort = std.sort;

fn minPlatform(arr: []usize, dep: []usize) usize {
    Sort.insertion(usize, arr, {}, Sort.asc(usize));
    Sort.insertion(usize, dep, {}, Sort.asc(usize));
    var platforms: usize = 1;
    var max_platforms: usize = 1;
    var arr_index: usize = 1;
    var dep_index: usize = 0;
    while (arr_index < arr.len and dep_index < arr.len) {
        if (arr[arr_index] <= dep[dep_index]) {
            platforms += 1;
            arr_index += 1;
        } else {
            platforms -= 1;
            dep_index += 1;
        }
        max_platforms = @max(max_platforms, platforms);
    }
    return max_platforms;
}

pub fn main() !void {
    var arr = [_]usize{ 900, 945, 955, 1100, 1500, 1800 };
    var dep = [_]usize{ 920, 1200, 1130, 1150, 1900, 2000 };
    const res = minPlatform(&arr, &dep);
    std.debug.print("Minimum number of platforms required  : {d}\n", .{res});
    // for (arr) |value| {
    //     std.debug.print("{d},", .{value});
    // }
    // std.debug.print("\n", .{});
    // for (dep) |value| {
    //     std.debug.print("{d},", .{value});
    // }
    // std.debug.print("\n", .{});
}
