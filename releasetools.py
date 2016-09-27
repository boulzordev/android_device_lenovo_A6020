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
  info.script.AppendExtra('ui_print("Copying device specific files.");')
  info.script.AppendExtra('run_program("/sbin/sh", "/tmp/install/bin/move_files.sh");')
  info.script.Unmount("/system")

def RestoreDeviceConfig(info):
  pass
