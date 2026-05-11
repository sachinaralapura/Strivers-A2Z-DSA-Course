const std = @import("std");
const Io = std.Io;
const root = @import("core");

const U = packed union(u16) {
    x: packed struct(u16) {
        data: u8,
        padding: u8,
    },
    y: u16,
};

pub fn main(init: std.process.Init) !void {
    const u: U = .{ .x = .{ .data = 12,.padding = 0 } };
    std.debug.print("{d}\n", .{u.x.data});
    const io = init.io;
    _ = io;
}
