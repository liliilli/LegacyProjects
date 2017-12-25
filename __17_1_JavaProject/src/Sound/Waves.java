package Sound;

import java.util.Random;

/**
 * Created by Vertx on 2017-05-09.
 */
public class Waves {
    public static class SinWave implements InterfaceSound.Instrument {
        @Override
        public byte[] createWave(double freq, int ms) {
            final int samples = ms * SAMPLE_RATE / 1000;
            byte[] output = new byte[samples];

            double period = (double) SAMPLE_RATE / freq;
            for (int i = 0; i < output.length; i++) {
                double angle = 2.0 * Math.PI / period;
                output[i] = (byte) (Math.sin(angle * i) * 127f);
            }

            return output;
        }
    }

    public static class PulseWave implements InterfaceSound.Instrument {
        @Override
        public byte[] createWave(double freq, int ms) {
            final int samples = ms * SAMPLE_RATE / 1000;
            byte[] output = new byte[samples];

            double period = (double) SAMPLE_RATE / freq;
            double angle = 2.0 * Math.PI / period;
            for (int i = 0; i < output.length; ++i) {
                if ((byte) (Math.sin(angle * i) * 127f) > 0) {
                    output[i] = 127;
                } else
                    output[i] = -127;
            }

            return output;
        }
    }

    public static class SawWave implements InterfaceSound.Instrument {
        @Override
        public byte[] createWave(double freq, int ms) {
            final int samples = ms * SAMPLE_RATE / 1000;
            byte[] output = new byte[samples];

            double period = (double) 2 * SAMPLE_RATE / freq;
            double value = -127.0;
            for (int i = 0; i < output.length; ++i) {
                if (value >= 127.0) value = -127.0;
                else value += 255.0 / period;

                output[i] = (byte) value;
            }

            return output;
        }
    }

    public static class TriangleWave implements InterfaceSound.Instrument {
        @Override
        public byte[] createWave(double freq, int ms) {
            final int samples = ms * SAMPLE_RATE / 1000;
            byte[] output = new byte[samples];

            double period = (double) SAMPLE_RATE / freq;
            double value = -127.0;
            boolean mSwitch = false;
            for (int i = 0; i < output.length; ++i) {
                if (!mSwitch) {
                    if (value >= 127.0) mSwitch = true;
                    else value += 255.0 / period;
                } else {
                    if (value <= -127.0) mSwitch = false;
                    else value -= 255.0 / period;
                }

                output[i] = (byte) value;
            }

            return output;
        }
    }

    public static class NoiseWave implements InterfaceSound.Instrument {
        @Override
        public byte[] createWave(double freq, int ms) {
            final int samples = ms * SAMPLE_RATE / 1000;
            byte[] output = new byte[samples];

            Random random = new Random();
            for (int i = 0; i < output.length; ++i) {
                output[i] = (byte) (random.nextInt(255) - 127);
            }

            return output;
        }
    }
}
