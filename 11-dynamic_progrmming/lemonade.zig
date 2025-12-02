const std = @import("std");
const Writer = std.Io.Writer;

const Bills = enum(u8) { Five = 5, Ten = 10, Twenty = 20 };
const BillCounter = struct {
    const Self = @This();
    inc_val: usize = 1,
    five_count: usize,
    ten_count: usize,
    twenty_count: usize,

    fn IncFive(self: *Self) void {
        self.five_count += self.inc_val;
    }

    fn DecFive(self: *Self) void {
        if (self.five_count > 0)
            self.five_count -= self.inc_val;
    }

    fn IncTen(self: *Self) void {
        self.ten_count += self.inc_val;
    }

    fn DecTen(self: *Self) void {
        if (self.ten_count > 0)
            self.ten_count -= self.inc_val;
    }

    fn IncTwenty(self: *Self) void {
        self.twenty_count += self.inc_val;
    }

    fn DecTwenty(self: *Self) void {
        if (self.twenty_count > 0)
            self.twenty_count -= self.inc_val;
    }
    pub fn format(self: Self, writer: *Writer) Writer.Error!void {
        try writer.print("BillCounter \n[\n five={},\n ten={},\n twenty={}\n]\n", .{ self.five_count, self.ten_count, self.twenty_count });
    }
};

fn lemonadeChanage(bills: []const usize) !bool {
    const out = std.fs.File.stdout();
    var buffer: [4096]u8 = undefined;
    var std_writer = out.writer(&buffer);
    const stdout = &std_writer.interface;
    var billCounter: BillCounter = .{ .five_count = 0, .ten_count = 0, .twenty_count = 0 };
    for (bills) |value| {
        const bill = std.meta.intToEnum(Bills, value) catch return false;
        switch (bill) {
            .Five => {
                billCounter.IncFive();
            },
            .Ten => {
                billCounter.IncTen();
                if (billCounter.five_count < 1) return false;
                billCounter.DecFive();
            },
            .Twenty => {
                billCounter.IncTwenty();
                if (billCounter.ten_count > 0 and billCounter.five_count > 0) {
                    billCounter.DecTen();
                    billCounter.DecFive();
                } else if (billCounter.five_count > 2) {
                    inline for (.{ 1, 2, 3 }) |_| {
                        billCounter.DecFive();
                    }
                } else {
                    return false;
                }
            },
        }
        try stdout.print("{f}\n", .{billCounter});
        try stdout.flush();
    }
    return true;
}

pub fn main() !void {
    const bills = [_]usize{ 5, 5, 5, 10, 20 };
    // const bills1 = [_]usize{ 5, 5, 10, 10, 20 };
    const result = try lemonadeChanage(&bills);
    std.debug.print("{}", .{result});
}
