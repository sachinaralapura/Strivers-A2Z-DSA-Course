const std = @import("std");
const ArrayList = std.ArrayList;
const Allocator = std.mem.Allocator;
const stack = @import("stack.zig");
const Stack = stack.Stack(i32);
const PairI32 = Pair(i32);
const PairStack = stack.Stack(PairI32);

var gpa = std.heap.GeneralPurposeAllocator(.{}).init;

fn Pair(comptime T: type) type {
    return struct {
        first: T,
        second: T,
    };
}

fn next_greater_brute(alloctor: Allocator, arr: []i32) !ArrayList(i32) {
    var ans = try ArrayList(i32).initCapacity(alloctor, arr.len);
    const n = arr.len;
    for (0..n) |i| {
        var j = i + 1;
        while (j % n != i) {
            if (arr[j % n] > arr[i]) {
                try ans.append(arr[j % n]);
                break;
            } else j += 1;
        }
        if (j % n == i) try ans.append(-1);
    }
    return ans;
}

fn next_greater_circular(allocator: Allocator, arr: []i32) !ArrayList(i32) {
    const n = arr.len;
    var ans = try ArrayList(i32).initCapacity(allocator, n);
    try ans.resize(n);
    for (ans.items) |*ele| ele.* = -1;
    var st = try Stack.init(allocator, n);
    var i = 2 * n - 1;
    while (i >= 0) : (i -= 1) {
        while (!st.isEmpty() and st.top().? <= arr[i % n])
            try st.pop();

        if (i < n) {
            if (!st.isEmpty()) ans.items[i] = st.top().?;
        }
        try st.push(arr[i % n]);
        if (i == 0) break;
    }
    return ans;
}

fn next_greater_circular_two(allocator: Allocator, arr: []i32) !ArrayList(i32) {
    const n = arr.len;
    var ans = try ArrayList(i32).initCapacity(allocator, n);
    try ans.resize(n);
    for (ans.items) |*ele| ele.* = -1;
    var st = try Stack.init(allocator, n);
    var i = n - 1;
    while (i > 0) : (i -= 1) {
        while (!st.isEmpty() and st.top().? <= arr[i]) {
            try st.pop();
        }
        if (!st.isEmpty()) {
            ans.items[i] = st.top().?;
        } else {
            ans.items[i] = -1;
        }
        try st.push(arr[i]);
    }

    // for first element
    while (!st.isEmpty() and st.top().? <= arr[0]) {
        try st.pop();
    }
    if (!st.isEmpty()) {
        ans.items[0] = st.top().?;
    } else {
        ans.items[0] = -1;
    }
    try st.push(arr[i]);

    while (!st.isEmpty() and st.top().? <= arr[n - 1]) {
        try st.pop();
    }

    if (!st.isEmpty()) {
        ans.items[n - 1] = st.top().?;
    } else {
        ans.items[n - 1] = -1;
    }

    return ans;
}

fn next_smaller_circular(allocator: Allocator, arr: []i32) !ArrayList(i32) {
    const n = arr.len;
    var ans = try ArrayList(i32).initCapacity(allocator, n);
    try ans.resize(n);
    for (ans.items) |*ele| ele.* = -1;
    var st = try Stack.init(allocator, n);
    var i = n - 1;
    while (i > 0) : (i -= 1) {
        while (!st.isEmpty() and st.top().? >= arr[i]) {
            try st.pop();
        }
        if (!st.isEmpty()) {
            ans.items[i] = st.top().?;
        } else {
            ans.items[i] = -1;
        }
        try st.push(arr[i]);
    }

    // for first element
    while (!st.isEmpty() and st.top().? >= arr[0]) {
        try st.pop();
    }
    if (!st.isEmpty()) {
        ans.items[0] = st.top().?;
    } else {
        ans.items[0] = -1;
    }
    try st.push(arr[i]);

    while (!st.isEmpty() and st.top().? >= arr[n - 1]) {
        try st.pop();
    }

    if (!st.isEmpty()) {
        ans.items[n - 1] = st.top().?;
    } else {
        ans.items[n - 1] = -1;
    }

    return ans;
}

pub fn next_smaller(allocator: Allocator, arr: []i32) ![]i32 {
    const n = arr.len;
    if (n == 0)
        return error.EMPTYARRAY;
    var ans = try ArrayList(i32).initCapacity(allocator, n);
    try ans.resize(n);
    for (ans.items) |*ele| ele.* = -1;
    var stk = try PairStack.init(allocator, n);
    var i = n - 1;
    while (true) {
        while (!stk.isEmpty() and stk.top().?.second >= arr[i]) try stk.pop();
        if (!stk.isEmpty()) ans.items[i] = stk.top().?.second;
        const newPair: PairI32 = .{ .first = @intCast(i), .second = arr[i] };
        try stk.push(newPair);
        // loop break
        if (i == 0) break;
        i -= 1;
    }
    return ans.toOwnedSlice();
}


// pub fn main() !void {
//     const allocator: Allocator = gpa.allocator();
//     var arr = try ArrayList(i32).initCapacity(allocator, 100);
//     try arr.appendSlice(&[_]i32{ 9, 1, 6, 7, 3, 4, 2, 9, 2, 1, 9, 7, 6, 1, 3, 2 });
//     defer arr.deinit();
//     const ans = try next_smaller(allocator, arr.items);
//     for (ans) |ele| {
//         std.debug.print("{d} ", .{ele});
//     }
// }
