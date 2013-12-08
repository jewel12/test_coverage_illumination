#!/usr/bin/env ruby

test_result_str = STDIN.readlines.find { |l| l =~ /^[.F*]+$/ }
test_results = test_result_str.split('').delete_if { |t| t !~ /^[F.]$/ }
print (test_results.find_all { |t| t == '.' }.size.to_f / test_results.size) * 100
