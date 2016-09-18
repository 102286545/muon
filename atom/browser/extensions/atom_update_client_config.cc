// Copyright 2015 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "base/command_line.h"
#include "base/version.h"
// #include "chrome/browser/component_updater/component_patcher_operation_out_of_process.h"
#include "atom/browser/extensions/atom_update_client_config.h"
// #include "chrome/browser/update_client/chrome_update_query_params_delegate.h"
#include "components/prefs/pref_service.h"
#include "content/public/browser/browser_context.h"
#include "content/public/browser/storage_partition.h"
#include "components/update_client/component_patcher_operation.h"

namespace extensions {

// For privacy reasons, requires encryption of the component updater
// communication with the update backend.
AtomUpdateClientConfig::AtomUpdateClientConfig(
    content::BrowserContext* context)
    : impl_(base::CommandLine::ForCurrentProcess(),
            content::BrowserContext::GetDefaultStoragePartition(context)->
                GetURLRequestContext(),
            true) {}

int AtomUpdateClientConfig::InitialDelay() const {
  return impl_.InitialDelay();
}

int AtomUpdateClientConfig::NextCheckDelay() const {
  return impl_.NextCheckDelay();
}

int AtomUpdateClientConfig::StepDelay() const {
  return impl_.StepDelay();
}

int AtomUpdateClientConfig::OnDemandDelay() const {
  return impl_.OnDemandDelay();
}

int AtomUpdateClientConfig::UpdateDelay() const {
  return 0;
}

std::vector<GURL> AtomUpdateClientConfig::UpdateUrl() const {
  return impl_.UpdateUrl();
}

std::vector<GURL> AtomUpdateClientConfig::PingUrl() const {
  return impl_.PingUrl();
}

base::Version AtomUpdateClientConfig::GetBrowserVersion() const {
  return impl_.GetBrowserVersion();
}

std::string AtomUpdateClientConfig::GetChannel() const {
  return "stable";
}

std::string AtomUpdateClientConfig::GetBrand() const {
  // TOOD
  return "";
}

std::string AtomUpdateClientConfig::GetLang() const {
  return "en-US";
  // return AtomUpdateQueryParamsDelegate::GetLang();
}

std::string AtomUpdateClientConfig::GetOSLongName() const {
  return impl_.GetOSLongName();
}

std::string AtomUpdateClientConfig::ExtraRequestParams() const {
  return impl_.ExtraRequestParams();
}

std::string AtomUpdateClientConfig::GetDownloadPreference() const {
  return std::string();
}

net::URLRequestContextGetter* AtomUpdateClientConfig::RequestContext() const {
  return impl_.RequestContext();
}

scoped_refptr<update_client::OutOfProcessPatcher>
AtomUpdateClientConfig::CreateOutOfProcessPatcher() const {
  LOG(INFO) << "----------------------"
    << "AtomutOfProcessPatcher";
  return nullptr; //make_scoped_refptr(nullptr/*new component_updater::AtomOutOfProcessPatcher*/);
}

bool AtomUpdateClientConfig::DeltasEnabled() const {
  LOG(INFO) << "Wanted deltas: " << impl_.DeltasEnabled();
  return false;//impl_.DeltasEnabled();
}

bool AtomUpdateClientConfig::UseBackgroundDownloader() const {
  return impl_.UseBackgroundDownloader();
}

bool AtomUpdateClientConfig::UseCupSigning() const {
  return impl_.UseCupSigning();
}

PrefService* AtomUpdateClientConfig::GetPrefService() const {
  return nullptr;
}

AtomUpdateClientConfig::~AtomUpdateClientConfig() {}

}  // namespace extensions
