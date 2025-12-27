const std = @import("std");
pub const Writer = std.Io.Writer;
pub const Order = std.math.Order;
pub const Sort = std.sort;
pub const Allocator = std.mem.Allocator;
pub const stdout = std.fs.File.stdout();
pub const ArrayList = std.ArrayList;
//---------------------------------------------------------------
// insertInterval.zig, mergeInterval.zig
/// Interval
/// represent start and end
pub const Interval = struct {
    start: usize,
    end: usize,
    const IntervalError = error{StartGreaterThanEnd};
    pub fn init(start: usize, end: usize) IntervalError!@This() {
        if (start > end) return IntervalError.StartGreaterThanEnd;
        return .{ .start = start, .end = end };
    }
    pub fn format(self: @This(), writer: *Writer) Writer.Error!void {
        try writer.print("start : {d} | end : {d}\n", .{ self.start, self.end });
    }
    pub fn AscStart(_: void, a: Interval, b: Interval) bool {
        return a.start < b.start;
    }
    pub fn DesStart(_: void, a: Interval, b: Interval) bool {
        return a.start > b.start;
    }
};

// mergeInterval.zig

// fractionalKnapsack.zig
pub const Item = struct {
    value: usize,
    weight: usize,
    pub fn perUnit(self: Item) f64 {
        return @as(f64, @floatFromInt(self.value)) / @as(f64, @floatFromInt(self.weight));
    }
};
pub fn ItemOrder(_: void, a: Item, b: Item) Order {
    const a_per_unit = a.perUnit();
    const b_per_unit = b.perUnit();
    if (a_per_unit < b_per_unit) return .gt;
    if (a_per_unit > b_per_unit) return .lt;
    return .eq;
}
pub const ItemPriority = std.PriorityQueue(Item, void, ItemOrder);

// Job_sequence.zig
pub const Job = struct {
    id: usize,
    deadline: usize,
    profit: usize,
    pub fn format(self: @This(), writer: *Writer) Writer.Error!void {
        try writer.print("[ Id : {d}, DeadLine : {d}, Profit : {d} ]\n", .{ self.id, self.deadline, self.profit });
    }
};

pub fn JobOrderProfit(_: void, a: Job, b: Job) bool {
    return a.profit > b.profit;
}

pub fn JobOrderId(_: void, a: Job, b: Job) bool {
    return a.id < b.id;
}

// largest_square.zig
pub fn CreateMatrix(comptime T: type) type {
    return struct {
        data: []T,
        rows: usize,
        cols: usize,
        allocator: Allocator,

        pub fn init(allocator: Allocator, rows: usize, cols: usize) !@This() {
            if (rows == 0 or cols == 0) {
                return error.InvalidDimensions;
            }
            const data = try allocator.alloc(T, rows * cols);
            @memset(data, 0);
            return @This(){ .data = data, .rows = rows, .cols = cols, .allocator = allocator };
        }

        pub fn deinit(self: *@This()) void {
            self.allocator.free(self.data);
            self.data = undefined;
            self.rows = 0;
            self.cols = 0;
        }

        fn checkBoundry(self: *const @This(), row: usize, col: usize) bool {
            return row >= self.rows or col >= self.cols;
        }

        pub fn get(self: *const @This(), row: usize, col: usize) !T {
            if (self.checkBoundry(row, col)) {
                return error.IndexOutOfBound;
            }
            return self.data[row * self.cols + col];
        }

        pub fn set(self: *@This(), row: usize, col: usize, value: T) !void {
            if (self.checkBoundry(row, col)) {
                return error.IndexOutOfBound;
            }
            self.data[row * self.cols + col] = value;
        }

        pub fn format(self: @This(), writer: *Writer) Writer.Error!void {
            try writer.print("Matrix ({d}x{d}) of type {s}:\n", .{ self.rows, self.cols, @typeName(T) });
        }
    };
}

// leastRecentJob.zig
pub const JobLru = struct {
    id: usize,
    value: []const u8,
    description: []const u8,

    pub fn init(id: usize, val: []const u8) @This() {
        return .{
            .id = id,
            .value = val,
            .description = "not set yet",
        };
    }

    pub fn format(self: @This(), writer: *Writer) Writer.Error!void {
        try writer.print("id : {d} | value : {s} | description : {s}\n", .{ self.id, self.value, self.description });
    }
};

// leastRecentJob.zig
pub fn Node(comptime T: type) type {
    return struct {
        const Self = @This();
        data: T,
        next: ?*Self = null,
        prev: ?*Self = null,

        pub fn init(allocator: Allocator, data: T) !*Self {
            const ptr = try allocator.create(Self);
            ptr.data = data;
            ptr.next = null;
            ptr.prev = null;
            return ptr;
        }
    };
}

// leastRecentJob.zig
pub fn hasId(comptime T: type, comptime K: type, fieldName: []const u8) void {
    comptime {
        if (!@hasField(T, fieldName))
            @compileError("Missing field " ++ fieldName ++ " should have field" ++ fieldName);

        if (@TypeOf(@field(@as(T, undefined), fieldName)) != K)
            @compileError("Field " ++ fieldName ++ " must be " ++ @typeName(K));
    }
}

// lemonade.zig
pub const BillCounter = struct {
    const Self = @This();
    pub const Bills = enum(u8) { Five = 5, Ten = 10, Twenty = 20 };
    inc_val: usize = 1,
    five_count: usize,
    ten_count: usize,
    twenty_count: usize,

    pub fn IncFive(self: *Self) void {
        self.five_count += self.inc_val;
    }

    pub fn DecFive(self: *Self) void {
        if (self.five_count > 0)
            self.five_count -= self.inc_val;
    }

    pub fn IncTen(self: *Self) void {
        self.ten_count += self.inc_val;
    }

    pub fn DecTen(self: *Self) void {
        if (self.ten_count > 0)
            self.ten_count -= self.inc_val;
    }

    pub fn IncTwenty(self: *Self) void {
        self.twenty_count += self.inc_val;
    }

    pub fn DecTwenty(self: *Self) void {
        if (self.twenty_count > 0)
            self.twenty_count -= self.inc_val;
    }
    pub fn format(self: Self, writer: *Writer) Writer.Error!void {
        try writer.print("BillCounter \n[\n five={},\n ten={},\n twenty={}\n]\n", .{ self.five_count, self.ten_count, self.twenty_count });
    }
};

// nMeetings
pub const Meeting = struct {
    start: usize,
    end: usize,
};
pub const MeetingList = std.ArrayList(Meeting);
pub fn MeetingOrder(_: void, a: Meeting, b: Meeting) bool {
    return a.end < b.end;
}
