// Jump Game - I

// Problem Statement: Given an array where each element represents the maximum number of steps
// you can jump forward from that element, return true if we can reach the last index starting from
//  the first index. Otherwise, return false.

// Jump Game 2

// Problem Statement: You are given a 0-indexed array nums of length n representing your maximum jump capability from each index.
// You start at index 0. Each element nums[i] represents the maximum number of steps you can jump forward from index i.
// Your goal is to reach the last index of the array (nums[n - 1]) using the minimum number of jumps
// Return the minimum number of jumps required to reach the last index.

const std = @import("std");

fn HaveZero(arr: []const usize) bool {
    for (arr) |value| if (value == 0) return true;
    return false;
}

fn JumpGameOne(jumps: []const usize) bool {
    var max_reach: usize = 0;
    for (jumps, 0..) |jump, i| {
        if (i > max_reach) return false;
        const reach = i + jump;
        max_reach = if (reach > max_reach) reach else max_reach;
        if (max_reach >= jumps.len - 1) return true;
    }
    return true;
}

// return minimum jump to reach end
fn JumpGameRec(arr: []const usize) usize {
    return JumpGameTwoRecursive(0, 0, arr);
}

fn JumpGameTwoRecursive(index: usize, jumps: usize, arr: []const usize) usize {
    if (jumps >= arr.len - 1) return 0;
    if (arr[index] == 0) return @intCast(std.math.maxInt(usize));
    var mini: usize = std.math.maxInt(usize);
    for (1..arr[index] + 1) |i| {
        mini = @min(mini, JumpGameTwoRecursive(index + i, jumps + 1, arr));
    }
    return mini;
}
const JumpGameError = error{
    CannotReachEnd,
    InfinityJump,
};

fn JumpGameTwo(arr: []const usize) JumpGameError!usize {
    var jumps: usize = 0;
    var left: usize = 0;
    var right: usize = 0;
    while (right < arr.len - 1) {
        var farthest: usize = 0;
        for (left..(right + 1)) |i| farthest = @max(farthest, i + arr[i]);
        if (farthest <= right) return JumpGameError.CannotReachEnd;
        left = right + 1;
        right = farthest;
        jumps += 1;
    }
    return jumps;
}

pub fn main() !void {
    const jumps = [_]usize{ 1, 2, 3, 1, 1, 0, 2, 5 };
    const result = JumpGameTwo(&jumps) catch |err| {
        std.debug.print("{s}\n", .{@errorName(err)});
        return;
    };
    std.debug.print("number of Jumps : {d}\n", .{result});
}
