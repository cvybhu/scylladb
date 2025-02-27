/*
 * Copyright (C) 2020-present ScyllaDB
 *
 */

/*
 * SPDX-License-Identifier: AGPL-3.0-or-later
 */

#pragma once

#include <seastar/core/sstring.hh>
#include <seastar/core/file.hh>
#include <seastar/core/sharded.hh>
#include <vector>
#include "sstables/version.hh"
#include "sstables/component_type.hh"
#include "sstables/shareable_components.hh"
#include "sstables/generation_type.hh"
#include <seastar/core/shared_ptr.hh>

namespace sstables {

struct entry_descriptor {
    sstring sstdir;
    sstring ks;
    sstring cf;
    generation_type generation;
    sstable_version_types version;
    sstable_format_types format;
    component_type component;

    static entry_descriptor make_descriptor(const std::filesystem::path& sst_path);

    // Use the given ks and cf and don't attempt to extract it from the dir path.
    // This allows loading sstables from any path, but the filename still has to be valid.
    static entry_descriptor make_descriptor(const std::filesystem::path& sst_path, sstring ks, sstring cf);

    entry_descriptor(std::string_view sstdir, sstring ks, sstring cf, generation_type generation,
                     sstable_version_types version, sstable_format_types format,
                     component_type component)
        : sstdir(sstdir), ks(ks), cf(cf), generation(generation), version(version), format(format), component(component) {}
};

// contains data for loading a sstable using components shared by a single shard;
// can be moved across shards
struct foreign_sstable_open_info {
    foreign_ptr<lw_shared_ptr<shareable_components>> components;
    std::vector<shard_id> owners;
    seastar::file_handle data;
    seastar::file_handle index;
    generation_type generation;
    sstable_version_types version;
    sstable_format_types format;
    uint64_t uncompressed_data_size;
    uint64_t metadata_size_on_disk;
};

struct sstable_open_config {
    // Load the first and last position in partition, populating the
    // `_first_partition_first_position` and `_last_partition_last_position`
    // fields respectively. Problematic sstables might fail to load. Set to
    // false if you want to disable this, to be able to read such sstables.
    // Should only be disabled for diagnostics purposes.
    // FIXME: Enable it by default once the root cause of large allocation when reading sstable in reverse is fixed.
    //  Ref: https://github.com/scylladb/scylladb/issues/11642
    bool load_first_and_last_position_metadata = false;
    // If the bloom filter is not loaded, the SSTable will use an always-present
    // filter, meaning that the SSTable will be opened on every single-partition
    // read.
    bool load_bloom_filter = true;
};

}
