// Problem Statement: Given an array representing a queue of customers and the value of bills they hold,
//  determine if it is possible to provide correct change to each customer. Customers can only pay with
//  5$, 10$ or 20$ bills and we initially do not have any change at hand. Return true, if it is possible
//  to provide correct change for each customer otherwise return false.

const std = @import("std");
const common = @import("common.zig");
const BillCounter = common.BillCounter;

fn lemonadeChanage(bills: []const usize) !bool {
    const out = std.fs.File.stdout();
    var buffer: [4096]u8 = undefined;
    var std_writer = out.writer(&buffer);
    const stdout = &std_writer.interface;
    var billCounter: BillCounter = .{ .five_count = 0, .ten_count = 0, .twenty_count = 0 };
    for (bills) |value| {
        const bill = std.meta.intToEnum(BillCounter.Bills, value) catch return false;
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
