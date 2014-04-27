from sensor import Sensor


class Alarm(object):

    def __init__(self, sensor=None):
        self._low_temp_threshold = 3
        self._high_temp_threshold = 28
        self._sensor = sensor or Sensor()
        self._is_alarm_on = False

    def check(self):
        motor_evn_temp_value = self._sensor.sample_temperature()
        if motor_evn_temp_value < self._low_temp_threshold \
                or self._high_temp_threshold < motor_evn_temp_value:
            self._is_alarm_on = True

    @property
    def is_alarm_on(self):
        return self._is_alarm_on
