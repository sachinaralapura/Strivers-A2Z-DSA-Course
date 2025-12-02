const std = @import("std");
const Order = std.math.Order;
const Allocator = std.mem.Allocator;

const Item = struct {
    value: usize,
    weight: usize,
    fn perUnit(self: Item) f64 {
        return @as(f64, @floatFromInt(self.value)) / @as(f64, @floatFromInt(self.weight));
    }
};

fn ItemOrder(_: void, a: Item, b: Item) Order {
    const a_per_unit = a.perUnit();
    const b_per_unit = b.perUnit();
    if (a_per_unit < b_per_unit) return .gt;
    if (a_per_unit > b_per_unit) return .lt;
    return .eq;
}

const ItemPriority = std.PriorityQueue(Item, void, ItemOrder);

fn FractionalKnapsack(allocator: Allocator, items: []const Item, sackSize: usize) !f64 {
    var items_priority = ItemPriority.init(allocator, {});
    defer items_priority.deinit();
    var total_value: f64 = 0;
    var remaining_weight = sackSize;
    for (items) |item| try items_priority.add(item);
    while (items_priority.removeOrNull()) |item| {
        // std.debug.print("value : {d} || weight : {d} || per_unit : {d}\n", .{ item.value, item.weight, item.perUnit() });
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
