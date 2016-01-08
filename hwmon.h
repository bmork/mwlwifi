/*
 * Copyright (C) 2016  Bjørn Mork <bjorn@mork.no>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 */

#ifndef _MWL_HWMON_H_
#define _MWL_HWMON_H_

#if IS_ENABLED(CONFIG_HWMON)
int mwl_hwmon_register(struct ieee80211_hw *hw);
void mwl_hwmon_unregister(struct ieee80211_hw *hw);
#else
static inline int mwl_hwmon_register(struct ieee80211_hw *hw) { return 0; }
static inline void mwl_hwmon_unregister(struct ieee80211_hw *hw) {}
#endif

#endif /* _MWL_HWMON_H_ */
