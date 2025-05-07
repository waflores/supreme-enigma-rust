& bazelisk run @rules_rust//tools/rust_analyzer:discover_bazel_rust_project # -- --bazel_arg=--watchfs 

write-host "There are a total of $($args.count) arguments"
for ( $i = 0; $i -lt $args.count; $i++ ) {
    write-host "Argument  $i is $($args[$i])"
}
