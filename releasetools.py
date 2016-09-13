# Copyright (C) 2016 The CyanogenMod Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

def IncrementalOTA_Assertions(info):
  AddAssertion(info)

def IncrementalOTA_VerifyBegin(info):
  # Workaround for apn list changes
  RestoreDeviceConfig(info)

def IncrementalOTA_InstallEnd(info):
  ReplaceDeviceConfig(info)

def FullOTA_Assertions(info):
  AddAssertion(info)

def FullOTA_InstallEnd(info):
  ReplaceDeviceConfig(info)

def AddAssertion(info):
  pass

def ReplaceDeviceConfig(info):
  info.script.Mount("/system")
  #info.script.AppendExtra('run_program("/sbin/sh", "-c", "mkdir /system/etc/firmware/venus_bak);')
  #info.script.AppendExtra('run_program("/sbin/sh", "-c", "cp /system/etc/venus.* /system/etc/firmware/venus_bak");')
  #S82918B1 a46
  #S82918D1 a40
  #S82918F1 l36
  #S82918G1 l37
  info.script.AppendExtra('run_program("/sbin/sh", "/tmp/install/bin/get_board_id.sh");')
  for b in ('default', 'A6020l36', 'A6020l37', 'A6020a40', 'A6020a46'):
    info.script.AppendExtra('if getprop("ro.product.variant") == "%s" then' % b)
    info.script.AppendExtra('ui_print("Variant %s detected");' % b)
    info.script.AppendExtra('run_program("/sbin/sh", "-c", "mv /system/etc/%s/venus* /system/etc/firmware/");' % b)
    info.script.AppendExtra('run_program("/sbin/sh", "-c", "mv /system/etc/%s/thermal* /system/etc/");' % b)
    info.script.AppendExtra('endif;')
  info.script.Unmount("/system")

def RestoreDeviceConfig(info):
  pass
