const std = @import("std");
const Allocator = std.mem.Allocator;
const Set = std.enums.EnumSet(Fruits);
const Map = std.AutoHashMap(Fruits, usize);

const MAX_FRUIT: usize = 2;
const Fruits = enum(usize) {
    Mango = 1,
    Banana = 2,
    PineApple = 3,
    Apple = 4,
    JackFruit = 5,
    Stawberry = 6,
};

fn fruitBaskets(trees: []const Fruits) !usize {
    var max_cout: usize = 0;
    for (trees, 0..) |_, i| {
        var fruit_set = Set.initEmpty();
        for (i..trees.len) |j| {
            fruit_set.insert(trees[j]);
            if (fruit_set.count() <= MAX_FRUIT) {
                max_cout = @max(max_cout, j - i + 1);
            } else break;
        }
    }
    return max_cout;
}

fn fruitBasketsTwoPointer(allocator: Allocator, trees: []const Fruits) !usize {
    var max_count: usize = 0;
    var left: usize = 0;
    var right: usize = 0;
    var fruit_map = Map.init(allocator);
    defer fruit_map.deinit();
    for (trees) |fruit| {
        var entry = try fruit_map.getOrPut(fruit);
        if (!entry.found_existing) {
            entry.value_ptr.* = 1;
        } else entry.value_ptr.* += 1;

        if (fruit_map.count() > MAX_FRUIT) {
            while (left < right and fruit_map.count() > MAX_FRUIT) {
                entry = try fruit_map.getOrPut(trees[left]);
                if (entry.found_existing) {
                    entry.value_ptr.* -= 1;
                    if (entry.value_ptr.* == 0) _ = fruit_map.remove(trees[left]);
                }
                left = left + 1;
            }
        }
        if (fruit_map.count() <= MAX_FRUIT) max_count = @max(max_count, right - left + 1);
        right = right + 1;
    }
    return max_count;
}

pub fn main() !void {
    var gpa = std.heap.GeneralPurposeAllocator(.{}).init;
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    const fruits = [_]Fruits{ Fruits.PineApple, Fruits.PineApple, Fruits.PineApple, Fruits.PineApple, Fruits.Mango, Fruits.Banana, Fruits.Mango, Fruits.Mango, Fruits.Banana, Fruits.PineApple, Fruits.PineApple, Fruits.Apple };
    const max: usize = try fruitBasketsTwoPointer(allocator, &fruits);
    std.debug.print("{d}", .{max});
}
