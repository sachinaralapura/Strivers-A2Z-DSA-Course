// Problem Statement: You are given an integer array nums and an integer k.
// Return the number of good subarrays of nums.

// A good subarray is defined as a contiguous subarray of nums that contains
// exactly k distinct integers. A subarray is a contiguous part of the array.

const std = @import("std");
const Allocator = std.mem.Allocator;
const Map = std.AutoHashMap(usize, usize);

fn brute(allocator: Allocator, arr: []const usize, k: usize) !usize {
    const n: usize = arr.len;
    var count: usize = 0;
    for (0..n) |i| {
        var mpp = Map.init(allocator);
        defer mpp.deinit();
        for (i..n) |j| {
            const entry = try mpp.getOrPut(arr[j]);
            if (!entry.found_existing) {
                entry.value_ptr.* = 1;
            } else entry.value_ptr.* += 1;
            if (mpp.count() == k) count += 1;
            if (mpp.count() > k) break;
        }
    }
    return count;
}

fn pp(allocator: Allocator, arr: []const usize, k: usize) !usize {
    var left: usize = 0;
    var right: usize = 0;
    var count: usize = 0;
    var mpp = Map.init(allocator);
    defer mpp.deinit();
    while (right < arr.len) {
        var entry = try mpp.getOrPut(arr[right]);
        if (!entry.found_existing) {
            entry.value_ptr.* = 1;
        } else entry.value_ptr.* += 1;

        while (mpp.count() > k) {
            entry = try mpp.getOrPut(arr[left]);
            if (entry.found_existing) entry.value_ptr.* -= 1;
            if (entry.value_ptr.* == 0) _ = mpp.remove(arr[left]);
            left += 1;
        }
        count += right - left + 1;
        right += 1;
    }
    return count;
}

fn optimal(allocator: Allocator, arr: []const usize, k: usize) !usize {
    return try pp(allocator, arr, k) - try pp(allocator, arr, k - 1);
}

pub fn main() !void {
    const arr = [_]usize{ 1, 2, 1, 3, 4 };
    const k: usize = 3;
    var gpa = std.heap.GeneralPurposeAllocator(.{}).init;
    const allocator: Allocator = gpa.allocator();
    const count = try optimal(allocator, &arr, k);
    std.debug.print("{d}", .{count});
}
