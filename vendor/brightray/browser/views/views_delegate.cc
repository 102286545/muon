// Copyright (c) 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE-CHROMIUM file.

#include "browser/views/views_delegate.h"

#include "ui/views/widget/desktop_aura/desktop_native_widget_aura.h"
#include "ui/views/widget/native_widget_aura.h"

#if defined(OS_LINUX)
#include "base/environment.h"
#include "base/nix/xdg_util.h"
#endif

namespace brightray {

ViewsDelegate::ViewsDelegate() {
}

ViewsDelegate::~ViewsDelegate() {
}

void ViewsDelegate::SaveWindowPlacement(const views::Widget* window,
                                        const std::string& window_name,
                                        const gfx::Rect& bounds,
                                        ui::WindowShowState show_state) {
}

bool ViewsDelegate::GetSavedWindowPlacement(
    const views::Widget* widget,
    const std::string& window_name,
    gfx::Rect* bounds,
    ui::WindowShowState* show_state) const {
  return false;
}

void ViewsDelegate::NotifyAccessibilityEvent(
    views::View* view, ax::mojom::Event event_type) {
}

void ViewsDelegate::NotifyMenuItemFocused(
    const base::string16& menu_name,
    const base::string16& menu_item_name,
    int item_index,
    int item_count,
    bool has_submenu) {
}

#if defined(OS_WIN)
HICON ViewsDelegate::GetDefaultWindowIcon() const {
  // Use current exe's icon as default window icon.
  return LoadIcon(GetModuleHandle(NULL), MAKEINTRESOURCE(1  /* IDR_MAINFRAME */));
}

HICON ViewsDelegate::GetSmallWindowIcon() const {
  return GetDefaultWindowIcon();
}

bool ViewsDelegate::IsWindowInMetro(gfx::NativeWindow window) const {
  return false;
}

#elif defined(OS_LINUX) && !defined(OS_CHROMEOS)
gfx::ImageSkia* ViewsDelegate::GetDefaultWindowIcon() const {
  return NULL;
}
#endif

views::NonClientFrameView* ViewsDelegate::CreateDefaultNonClientFrameView(
    views::Widget* widget) {
  return NULL;
}

void ViewsDelegate::AddRef() {
}

void ViewsDelegate::ReleaseRef() {
}

void ViewsDelegate::OnBeforeWidgetInit(
    views::Widget::InitParams* params,
    views::internal::NativeWidgetDelegate* delegate) {
  // If we already have a native_widget, we don't have to try to come
  // up with one.
  if (params->native_widget)
    return;

  if (params->parent &&
      params->type != views::Widget::InitParams::TYPE_MENU &&
      params->type != views::Widget::InitParams::TYPE_TOOLTIP) {
    params->native_widget = new views::NativeWidgetAura(delegate);
  } else {
    params->native_widget = new views::DesktopNativeWidgetAura(delegate);
  }
}


base::TimeDelta ViewsDelegate::GetTextfieldPasswordRevealDuration() {
  return base::TimeDelta();
}

#if defined(OS_LINUX)
namespace {

bool IsDesktopEnvironmentUnity() {
  std::unique_ptr<base::Environment> env(base::Environment::Create());
  base::nix::DesktopEnvironment desktop_env =
      base::nix::GetDesktopEnvironment(env.get());
  return desktop_env == base::nix::DESKTOP_ENVIRONMENT_UNITY;
}

}  // namespace
#endif

bool ViewsDelegate::WindowManagerProvidesTitleBar(bool maximized) {
#if defined(OS_LINUX)
  // On Ubuntu Unity, the system always provides a title bar for
  // maximized windows.
  //
  // TODO(thomasanderson): Consider using the _UNITY_SHELL wm hint
  // when support for Ubuntu Trusty is dropped.
  if (!maximized)
    return false;
  static bool is_desktop_environment_unity = IsDesktopEnvironmentUnity();
  return is_desktop_environment_unity;
#else
  return false;
#endif
}

}  // namespace brightray
