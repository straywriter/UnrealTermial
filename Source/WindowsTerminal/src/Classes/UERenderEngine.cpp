
#include "UERenderEngine.h"

// UERenderEngine::UERenderEngine(FWindowsTerminalAdapter Adapter)
// {
// }

HRESULT UERenderEngine::StartPaint() noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::EndPaint() noexcept
{
	return S_OK;

}

bool UERenderEngine::RequiresContinuousRedraw() noexcept
{
	return S_OK;

}

void UERenderEngine::WaitUntilCanRender() noexcept
{

}

HRESULT UERenderEngine::Present() noexcept
{
	return S_OK;

}


HRESULT UERenderEngine::ScrollFrame() noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::Invalidate(const til::rect* psrRegion) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::InvalidateCursor(const til::rect* psrRegion) noexcept
{
				return S_OK;
	
}

HRESULT UERenderEngine::InvalidateSystem(const til::rect* prcDirtyClient) noexcept
{
	return S_OK;

}


HRESULT UERenderEngine::InvalidateHighlight(std::span<const til::point_span> highlights,
	const TextBuffer& buffer) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::InvalidateScroll(const til::point* pcoordDelta) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::InvalidateAll() noexcept
{
	return S_OK;

}


HRESULT UERenderEngine::InvalidateTitle(std::wstring_view proposedTitle) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::NotifyNewText(const std::wstring_view newText) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::PrepareRenderInfo(RenderFrameInfo info) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::ResetLineTransform() noexcept
{
				return S_OK;
	
}

HRESULT UERenderEngine::PrepareLineTransform(LineRendition lineRendition, til::CoordType targetRow,
	til::CoordType viewportLeft) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::PaintBackground() noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::PaintBufferLine(std::span<const Cluster> clusters, til::point coord, bool fTrimLeft,
	bool lineWrapped) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::PaintBufferGridLines(const GridLineSet lines, const COLORREF gridlineColor,
	const COLORREF underlineColor, const size_t cchLine, const til::point coordTarget) noexcept
{
				return S_OK;
	
}

HRESULT UERenderEngine::PaintSelection(const til::rect& rect) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::PaintCursor(const CursorOptions& options) noexcept
{
				return S_OK;
	
}

HRESULT UERenderEngine::UpdateDrawingBrushes(const TextAttribute& textAttributes, const RenderSettings& renderSettings,
	gsl::not_null<IRenderData*> pData, bool usingSoftFont, bool isSettingDefaultBrushes) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::UpdateFont(const FontInfoDesired& FontInfoDesired, FontInfo& FontInfo) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::UpdateSoftFont(std::span<const uint16_t> bitPattern, til::size cellSize,
	size_t centeringHint) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::UpdateDpi(int iDpi) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::UpdateViewport(const til::inclusive_rect& srNewViewport) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::GetProposedFont(const FontInfoDesired& FontInfoDesired, FontInfo& FontInfo, int iDpi) noexcept
{
	return S_OK;
}

HRESULT UERenderEngine::GetDirtyArea(std::span<const til::rect>& area) noexcept
{
	// x 宽, y 高
	// static constexpr til::rect empty(0, 0, static_cast<til::CoordType>(Adapter.Size.X), static_cast<til::CoordType>(Adapter.Size.Y));
	// static constexpr til::rect empty(0, 0, 0, 0);
	// area = { &empty, 1 };

	return S_OK;
}

HRESULT UERenderEngine::GetFontSize(til::size* pFontSize) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::IsGlyphWideByFont(std::wstring_view glyph, bool* pResult) noexcept
{
	return S_OK;

}

HRESULT UERenderEngine::UpdateTitle(std::wstring_view newTitle) noexcept
{
	return S_OK;

}

void UERenderEngine::UpdateHyperlinkHoveredId(uint16_t hoveredId) noexcept
{

}
