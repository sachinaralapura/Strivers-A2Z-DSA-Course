// Problem Statement: Given a value V, if we want to make a change for V Rs,
//  and we have an infinite supply of each of the denominations in Indian currency,
//  i.e., we have an infinite supply of { 1, 2, 5, 10, 20, 50, 100, 500, 1000}
//  valued coins/notes, what is the minimum number of coins and/or notes needed to make the change.

const std = @import("std");
const ArrayList = std.ArrayList(usize);
const Allocator = std.mem.Allocator;
const Denominatin = [_]usize{ 1000, 500, 100, 50, 20, 10, 5, 2, 1 };
const LinkedList = std.SinglyLinkedList;
fn minCoin(allocator: Allocator, value: usize) ![]usize {
    var remaining = value;
    var no_of_coins: usize = 0;
    var result = try ArrayList.initCapacity(allocator, 0);
    defer result.deinit(allocator);
    for (Denominatin) |coin_value| {
        while (coin_value <= remaining) {
            remaining -= coin_value;
            try result.append(allocator, coin_value);
            no_of_coins += 1;
        }
    }
    return result.toOwnedSlice(allocator);
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    const value: usize = 81;
    const result = try minCoin(allocator, value);
    for (result) |v|
        std.debug.print("{d} ", .{v});
    defer allocator.free(result);
}
