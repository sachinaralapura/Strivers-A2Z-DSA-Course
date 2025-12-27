// There are n children standing in a line. Each child is assigned a rating value given in the integer array ratings.
// You are giving candies to these children subjected to the following requirements:
//     Each child must have at least one candy.
//     Children with a higher rating get more candies than their neighbors.
// Return the minimum number of candies you need to have to distribute the candies to the children.

const std = @import("std");
const Allocator = std.mem.Allocator;

fn candyBrute(allocator: Allocator, ratings: []const usize) !usize {
    var left = try allocator.alloc(usize, ratings.len);
    var right = try allocator.alloc(usize, ratings.len);
    left[0] = 1;
    right[ratings.len - 1] = 1;

    // fron left to right
    for (1..ratings.len) |i| {
        if (ratings[i] > ratings[i - 1]) {
            left[i] = left[i - 1] + 1;
        } else left[i] = 1;
    }

    // from right to left
    {
        var i: usize = ratings.len - 1;
        while (i > 0) {
            i -= 1;
            if (ratings[i] > ratings[i + 1]) {
                right[i] = right[i + 1] + 1;
            } else right[i] = 1;
        }
    }

    var sum: usize = 0;
    for (0..ratings.len) |i| sum += @max(left[i], right[i]);

    allocator.free(left);
    allocator.free(right);
    return sum;
}

fn candySlope(ratings: []const usize) usize {
    const n: usize = ratings.len;
    var sum: usize = 1;

    var i: usize = 1;
    while (i < n) {
        if (ratings[i] == ratings[i - 1]) {
            sum += 1;
            i += 1;
            continue;
        }

        var peak: usize = 1;
        while (i < n and ratings[i] > ratings[i - 1]) {
            peak += 1;
            sum += peak;
            i += 1;
        }

        var down: usize = 1;
        while (i < n and ratings[i] < ratings[i - 1]) {
            sum += down;
            down += 1;
            i += 1;
        }
        if (down > peak) {
            sum += (down - peak);
        }
    }
    return sum;
}

pub fn main() !void {
    var ratings = [_]usize{ 1, 3, 6, 8, 9, 5, 3 };

    // var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    // defer _ = gpa.deinit();
    // const allocator = gpa.allocator();

    // const result: usize = try candyBrute(allocator, &ratings);
    const result: usize = candySlope(&ratings);
    std.debug.print("{d}", .{result});
}
