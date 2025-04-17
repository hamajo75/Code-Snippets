#!/usr/bin/env python3

from dataclasses import dataclass

@dataclass
class HWVersion:
    item_type: str = ""
    item_type_nr: str = ""
    major: int = 0
    minor: int = 0
    patch: int = 0


class Static:
    hw_version = None

    @staticmethod
    def fetch_hw_version():
        Static.hw_version = HWVersion("item_type", "0000614", 1, 2, 3)

    @staticmethod
    def is_new_hw() -> bool:
        if Static.hw_version is None:
            Static.fetch_hw_version()

        if Static.hw_version.item_type_nr == "0000614":
            return True
        return False


print(Static.is_new_hw())
