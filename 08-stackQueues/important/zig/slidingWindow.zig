const std = @import("std");
const Allocator = std.mem.Allocator;
const Deque = @import("Deque.zig").Deque(usize);
const ArrayListI32 = std.ArrayList(i32);
const LL = std.SinglyLinkedList(usize);

const Error = error{WINDOWTOOBIG};

fn GetMax(arr: []const i32, l: usize, r: usize, ans: *ArrayListI32) !void {
    var maxi: i32 = std.math.minInt(i32);
    var i = l;
    while (i <= r) : (i += 1) maxi = @max(arr[i], maxi);
    try ans.append(maxi);
}

fn SlidingWindow(allocator: Allocator, arr: []const i32, k: usize) !ArrayListI32 {
    const n = arr.len;
    if (k > n) return Error.WINDOWTOOBIG;
    var l: usize = 0;
    var r: usize = l + k - 1;
    var ans = ArrayListI32.init(allocator);
    while (r < n) {
        try GetMax(arr, l, r, &ans);
        l += 1;
        r += 1;
    }
    return ans;
}

fn SlidingWindowDeque(allocator: Allocator, arr: []const i32, k: usize) !ArrayListI32 {
    const n = arr.len;
    if (k > n) return Error.WINDOWTOOBIG;
    var dq: Deque = try Deque.init(allocator);
    var ans = ArrayListI32.init(allocator);
    for (arr, 0..) |curr, i| {
        if (!dq.isEmpty() and dq.front().?.* == (i -% k)) {
            _ = dq.popFront().?;
        }
        while (!dq.isEmpty() and arr[dq.back().?.*] < curr) {
            _ = dq.popBack().?;
        }
        try dq.pushBack(i);
        if (i >= k - 1) {
            try ans.append(arr[dq.front().?.*]);
        }
    }
    return ans;
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}).init;
    const allocator: Allocator = gpa.allocator();
    const arr = [_]i32{ 4, 0, -1, 3, 5, 3, 6, 8 };
    const k: usize = 3;
    if (SlidingWindowDeque(allocator, arr[0..], k)) |results| {
        defer results.deinit();
        for (results.items) |item| {
            std.debug.print("{}\n", .{item});
        }
    } else |err| switch (err) {
        Error.WINDOWTOOBIG => {
            std.debug.print("Error: window size is bigger than the array size\n", .{});
        },
        error.OutOfMemory => {
            std.debug.print("Error: Out of memory\n", .{});
        },
    }
}
