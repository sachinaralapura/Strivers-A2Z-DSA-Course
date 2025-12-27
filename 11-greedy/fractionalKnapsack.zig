// Problem Statement: The weight of N items and their corresponding values are given.
//  We have to put these items in a knapsack of weight W such that the total value obtained is maximized.

const std = @import("std");
const Allocator = std.mem.Allocator;
const common = @import("common.zig");
const Item = common.Item;
const ItemOrder = common.ItemOrder;
const ItemPriority = common.ItemPriority;

fn FractionalKnapsack(allocator: Allocator, items: []const Item, sackSize: usize) !f64 {
    var items_priority = ItemPriority.init(allocator, {});
    defer items_priority.deinit();
    var total_value: f64 = 0;
    var remaining_weight = sackSize;
    for (items) |item| try items_priority.add(item);
    while (items_priority.removeOrNull()) |item| {
        if (remaining_weight < item.weight) {
            total_value += item.perUnit() * @as(f64, @floatFromInt(remaining_weight));
            break;
        } else {
            total_value += @as(f64, @floatFromInt(item.value));
            remaining_weight -= item.weight;
        }
    }
    return total_value;
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();

    const sack_size: usize = 90;
    const items = [_]Item{
        .{ .value = 100, .weight = 20 },
        .{ .value = 60, .weight = 10 },
        .{ .value = 100, .weight = 50 },
        .{ .value = 200, .weight = 50 },
    };

    const total_value = try FractionalKnapsack(allocator, &items, sack_size);
    std.debug.print("Total value : {d}", .{total_value});
}
