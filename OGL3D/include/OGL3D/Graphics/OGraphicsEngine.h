#pragma once
#include <OGL3D/Math/OVec4.h>

class OGraphicsEngine
{
public:
	OGraphicsEngine();
	~OGraphicsEngine();

public:
	void clear(const OVec4& color);         //�ŧi�@�Ӧ������ clear,�Ω󱵦��@�� OVec4 ���O���`�q�ޥΰѼ�,�q�`�Ω�M���Y�ت��A�γ]�m�I���C�⪺���
};