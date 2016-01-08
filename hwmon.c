/*
 * Copyright (C) 2016  Bjørn Mork <bjorn@mork.no>
 */

#include <linux/hwmon.h>
#include "sysadpt.h"
#include "dev.h"
#include "fwcmd.h"
#include "hwmon.h"

#if IS_ENABLED(CONFIG_HWMON)
static ssize_t temp1_input_show(struct device *device,
				struct device_attribute *devattr,
				char *buf)
{
	u32 temp;
	struct ieee80211_hw *hw = dev_get_drvdata(device);
	int ret = mwl_fwcmd_get_temp(hw, &temp);

	/* 'temp' appears to be Fahrenheit despite the 'celcius' field name */
	return ret < 0 ? ret : snprintf(buf, PAGE_SIZE, "%d\n", (temp - 32) * 1000 * 5 / 9);
}
static DEVICE_ATTR_RO(temp1_input);

static struct attribute *mwl_hwmon_attrs[] = {
	&dev_attr_temp1_input.attr,
	NULL,
};
ATTRIBUTE_GROUPS(mwl_hwmon);

int mwl_hwmon_register(struct ieee80211_hw *hw)
{
	struct mwl_priv *priv = hw->priv;
	struct device *hwmon;

	hwmon = hwmon_device_register_with_groups(priv->dev, wiphy_name(hw->wiphy),
						  hw, mwl_hwmon_groups);
	if (!IS_ERR(hwmon))
		priv->hwmon = hwmon;
	return PTR_ERR_OR_ZERO(hwmon);
}

void mwl_hwmon_unregister(struct ieee80211_hw *hw)
{
	struct mwl_priv *priv = hw->priv;

	if (priv->hwmon)
		hwmon_device_unregister(priv->hwmon);
	priv->hwmon = NULL;
}
#endif /* CONFIG_HWMON */

