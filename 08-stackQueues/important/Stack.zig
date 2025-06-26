const std = @import("std");
const Allocator = std.mem.Allocator;
pub const Stack = struct {
    items: []u32,
    capacity: usize,
    length: usize,
    allocator: Allocator,

    pub fn init(allocator: Allocator, capacity: usize) !Stack {
        var buffer = try allocator.alloc(u32, capacity);
        return Stack{ .items = buffer[0..], .capacity = capacity, .length = 0, .allocator = allocator };
    }

    pub fn push(self: *Stack, data: u32) !void {
        if (!self.ensureTotalCapacity(self.length + 1)) {
            var new_buffer = try self.allocator.alloc(u32, self.capacity * 2);
            @memcpy(new_buffer[0..self.capacity], self.items);
            self.allocator.free(self.items);
            self.items = new_buffer;
            self.capacity *= 2;
        }
        self.items[self.length] = data;
        self.length += 1;
    }

    pub fn pop(self: *Stack) !void {
        if (self.length == 0) return error.StackEmpty;
        self.items[self.length - 1] = undefined;
        self.length -= 1;
    }

    pub fn top(self: *Stack) ?u32 {
        if (self.length == 0) return null;
        return self.items[self.length - 1];
    }

    pub fn isEmpty(self: *Stack) bool {
        return self.length == 0;
    }
    pub fn deinit(self: *Stack) void {
        self.allocator.free(self.items);
    }

    fn ensureTotalCapacity(self: *Stack, newLength: usize) bool {
        if (newLength >= self.capacity) return false;
        return true;
    }
};

pub fn GStack(comptime T: type) type {
    return struct {
        items: []T,
        capacity: usize,
        length: usize,
        allocator: Allocator,
        const Self = @This();

        pub fn init(allocator: Allocator, capacity: usize) !Self {
            var buffer = try allocator.alloc(T, capacity);
            return .{ .items = buffer[0..], .capacity = capacity, .length = 0, .allocator = allocator };
        }

        pub fn push(self: *Self, data: T) !void {
            if (!self.ensureTotalCapacity(self.length + 1)) {
                var new_buffer = try self.allocator.alloc(T, self.capacity * 2);
                @memcpy(new_buffer[0..self.capacity], self.items);
                self.allocator.free(self.items);
                self.items = new_buffer;
                self.capacity *= 2;
            }
            self.items[self.length] = data;
            self.length += 1;
        }

        pub fn pop(self: *Self) !void {
            if (self.length == 0) return error.StackEmpty;
            self.items[self.length - 1] = undefined;
            self.length -= 1;
        }

        pub fn top(self: *const Self) ?T {
            if (self.length == 0) return null;
            return self.items[self.length - 1];
        }

        pub fn isEmpty(self: *const Self) bool {
            return self.length == 0;
        }
        pub fn deinit(self: *const Self) void {
            self.allocator.free(self.items);
        }

        fn ensureTotalCapacity(self: *const Self, newLength: usize) bool {
            if (newLength >= self.capacity) return false;
            return true;
        }
    };
}
