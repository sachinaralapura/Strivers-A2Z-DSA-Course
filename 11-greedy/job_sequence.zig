// Problem Statement: You are given a set of N jobs where each job comes with a deadline and profit.
//  The profit can only be earned upon completing the job within its deadline.
//  Find the number of jobs done and the maximum profit that can be obtained.
//  Each job takes a single unit of time and only one job can be performed at a time.

const std = @import("std");
const Allocator = std.mem.Allocator;
const ArrayList = std.ArrayList(usize);
const Writer = std.Io.Writer;

const common = @import("common.zig");
const Sort = common.Sort;
const Job = common.Job;
const JobOrderId = common.JobOrderId;
const JobOrderProfit = common.JobOrderProfit;

const JobSequence = struct {
    const Self = @This();
    jobs: []Job,
    allocator: Allocator,

    pub fn init(allocator: Allocator, jobs: []Job) Self {
        return Self{ .jobs = jobs, .allocator = allocator };
    }

    pub fn perform(self: *Self) !struct { usize, usize, []usize } {
        Sort.insertion(Job, self.jobs, {}, JobOrderProfit);

        var max_deadline: usize = 0;
        for (self.jobs) |job| max_deadline = @max(max_deadline, job.deadline);

        var time_slot = try ArrayList.initCapacity(self.allocator, max_deadline);
        defer time_slot.deinit(self.allocator);
        try time_slot.resize(self.allocator, max_deadline + 1);
        @memset(time_slot.items, 0);

        var count_jobs: usize = 0;
        var total_profit: usize = 0;
        for (self.jobs) |job| {
            var i: usize = job.deadline;
            while (i > 0) : (i -= 1) {
                if (time_slot.items[i] == 0) {
                    time_slot.items[i] = job.id;
                    count_jobs += 1;
                    total_profit += job.profit;
                    break;
                }
            }
        }
        return .{ count_jobs, total_profit, try time_slot.toOwnedSlice(self.allocator) };
    }
};

pub fn main() !void {
    const out = std.fs.File.stdout();
    var buffer: [4096]u8 = undefined;
    var std_writer = out.writer(&buffer);
    const stdout = &std_writer.interface;

    var gpa = std.heap.GeneralPurposeAllocator(.{}){};
    defer _ = gpa.deinit();
    const allocator = gpa.allocator();
    var jobs = [_]Job{
        .{ .id = 6, .deadline = 2, .profit = 80 },
        .{ .id = 3, .deadline = 6, .profit = 70 },
        .{ .id = 4, .deadline = 6, .profit = 65 },
        .{ .id = 2, .deadline = 5, .profit = 60 },
        .{ .id = 5, .deadline = 4, .profit = 25 },
        .{ .id = 8, .deadline = 2, .profit = 22 },
        .{ .id = 1, .deadline = 4, .profit = 20 },
        .{ .id = 7, .deadline = 2, .profit = 10 },
    };

    var job_sequence: JobSequence = JobSequence.init(allocator, &jobs);
    const result = try job_sequence.perform();
    std.debug.print("Job counts : {d} || Total Profit : {d}\n", .{ result.@"0", result.@"1" });

    const time_slot = result.@"2";
    defer allocator.free(time_slot);

    for (time_slot) |slot| {
        if (FindInJobs(&jobs, slot)) |job_index| try stdout.print("{f}", .{jobs[job_index]});
        try stdout.flush();
    }
}

fn add() callconv(.c) !void {}

fn FindInJobs(jobs: []const Job, id: usize) ?usize {
    for (jobs, 0..) |job, i| {
        if (job.id == id) return i;
    }
    return null;
}

fn FindInJobsBinary(jobs: []const Job, id: usize) ?usize {
    var left: usize = 0;
    var right: usize = jobs.len;
    while (left < right) {
        const mid = (left + right) / 2;
        if (jobs[mid].id == id) return mid;
        if (jobs[mid].id < id) left = mid + 1 else right = mid;
    }
    return null;
}
