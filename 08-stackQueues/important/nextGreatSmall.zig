const std = @import("std");
const ArrayList = std.ArrayList;
const Allocator = std.mem.Allocator;
const Stack = @import("Stack.zig").GStack(i32);

var gpa = std.heap.GeneralPurposeAllocator(.{}).init;

fn next_greater(alloctor: Allocator, arr: []i32) !ArrayList(i32) {
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

fn next_greater_opt(allocator: Allocator, arr: []i32) !ArrayList(i32) {
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

fn next_greater_two_opt(allocator: Allocator, arr: []i32) !ArrayList(i32) {
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

fn next_smaller_two_opt(allocator: Allocator, arr: []i32) !ArrayList(i32) {
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
pub fn main() !void {
    const allocator: Allocator = gpa.allocator();
    var arr = try ArrayList(i32).initCapacity(allocator, 100);
    try arr.appendSlice(&[_]i32{ 2, 3, 1, 6, 7, 9, 1, 2, 10, 2, 4, 3, 7, 6, 1, 10 });
    defer arr.deinit();
    var ans = try next_smaller_two_opt(allocator, arr.items);
    defer ans.deinit();
    for (ans.items) |ele| {
        std.debug.print("{d}\n", .{ele});
    }
}
