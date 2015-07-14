#ifndef ANIMATION_FRAME_DATA_
#define ANIMATION_FRAME_DATA_

class AnimationFrameData
{
public:
	AnimationFrameData(int tileId, int duration)
	{
		tileId_ = tileId;
		duration_ = duration;
	}

	int getTileId() const { return tileId_; }
	int getDuration() const { return duration_; }
private:
	int tileId_;
	int duration_;
};

#endif