const std = @import("std");
const common = @import("common.zig");
const Matrix = common.CreateMatrix;
const Allocator = std.mem.Allocator;
var gpa = std.heap.GeneralPurposeAllocator(.{}).init;

const BMatrix = Matrix(u8);
const DpMatrix = Matrix(usize);

fn largest_sqare(allocator: Allocator, mat: *const BMatrix) !usize {
    const n: usize = mat.rows;
    const m: usize = mat.cols;
    var dp: DpMatrix = try DpMatrix.init(allocator, n, m);
    defer dp.deinit();

    var max: usize = 0;
    for (0..n) |i| {
        for (0..m) |j| {
            const val = try mat.get(i, j);
            if (val == 0) continue;

            var left: usize, var top: usize, var diag: usize = .{ 0, 0, 0 };

            if (i > 0 and j > 0) {
                left = try dp.get(i, j - 1);
                top = try dp.get(i - 1, j);
                diag = try dp.get(i - 1, j - 1);
            }
            const dpValue = @min(left, top, diag) + 1;
            if (dpValue > max) {
                max = dpValue;
            }
            try dp.set(i, j, dpValue);
        }
    }
    std.debug.print("{f}", .{dp});
    return max;
}

pub fn main() !void {
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    var prng = std.Random.DefaultPrng.init(@intCast(std.time.nanoTimestamp()));
    var rng = prng.random();

    const rows: usize = 100;
    const cols: usize = 100;

    var matrix: BMatrix = try BMatrix.init(allocator, rows, cols);
    defer matrix.deinit();

    for (0..rows) |i| {
        for (0..cols) |j| {
            try matrix.set(i, j, @intFromBool(rng.boolean()));
            try matrix.set(i, j, 1);
        }
    }
    std.debug.print("{f}", .{matrix});

    const largest: usize = try largest_sqare(allocator, &matrix);
    std.debug.print("{d}\n", .{largest});
}
