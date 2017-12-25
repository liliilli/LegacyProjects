package Sound;

import Game.Resources.Sounds.SoundWalk;
import com.sun.istack.internal.Nullable;

import javax.sound.sampled.AudioFormat;
import javax.sound.sampled.AudioSystem;
import javax.sound.sampled.LineUnavailableException;
import javax.sound.sampled.SourceDataLine;

import Custom.Pair;

import static Sound.InterfaceSound.Instrument.SAMPLE_RATE;

public class SoundSystem implements InterfaceSound.System {
    private static SoundSystem mInstance = new SoundSystem();

    private InterfaceSound.Instrument[] mInstrument = new InterfaceSound.Instrument[5];

    private final AudioFormat af = new AudioFormat(SAMPLE_RATE, 16, 1, true, true);
    private SourceDataLine mLine = null;

    private SoundSystem() {
        mInstrument[0] = new Waves.SinWave();
        mInstrument[1] = new Waves.PulseWave();
        mInstrument[2] = new Waves.SawWave();
        mInstrument[3] = new Waves.TriangleWave();
        mInstrument[4] = new Waves.NoiseWave();
    }

    public static SoundSystem getInstance() {
        if (mInstance == null)
            mInstance = new SoundSystem();
        return mInstance;
    }

    @Override
    public void play(AbstractSound sound) {
        assert sound != null;

        try {
            startSoundLine();
            for (Pair<Note, Integer> note : sound.getContainer()) {
                output(0, note.getFirst().getFrequency(), note.getSecond());
            }
        } catch (LineUnavailableException e) {
            e.printStackTrace();
        } finally {
            endSoundLine();
        }
    }

    private void output(int i, double freq, int milliseconds) {
        byte[] toneBuffer = mInstrument[i].createWave(freq, milliseconds);
        mLine.write(toneBuffer, 0, toneBuffer.length);
    }

    private void startSoundLine() throws LineUnavailableException {
        mLine = AudioSystem.getSourceDataLine(af);
        mLine.open(af, SAMPLE_RATE);
        mLine.start();
    }

    private void endSoundLine() {
        mLine.drain();
        mLine.close();
    }
}

