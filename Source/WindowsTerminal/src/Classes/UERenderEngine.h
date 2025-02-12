#pragma once


#include "UnrealTerminalContext.h"

UE_PUSH_MACRO("check")
#undef check
THIRD_PARTY_INCLUDES_START
#include "LibraryIncludes.h"
#include "IRenderEngine.hpp"
THIRD_PARTY_INCLUDES_END
UE_POP_MACRO("check")

using namespace Microsoft::Console::Render;

class UERenderEngine final : public /*Microsoft::Console::Render::*/IRenderEngine
{
public:

	// UERenderEngine(FWindowsTerminalAdapter Adapter);
	//
	// void Set(FWindowsTerminalAdapter InAdapter){ Adapter = InAdapter;}

	// Begin IRenderEngine
	[[nodiscard]] HRESULT StartPaint() noexcept override;
	[[nodiscard]] HRESULT EndPaint() noexcept override;
	[[nodiscard]] bool RequiresContinuousRedraw() noexcept override;
	void WaitUntilCanRender() noexcept override;
	[[nodiscard]] HRESULT Present() noexcept override;
	[[nodiscard]] HRESULT ScrollFrame() noexcept override;
	[[nodiscard]] HRESULT Invalidate(const til::rect* psrRegion) noexcept override;
	[[nodiscard]] HRESULT InvalidateCursor(const til::rect* psrRegion) noexcept override;
	[[nodiscard]] HRESULT InvalidateSystem(const til::rect* prcDirtyClient) noexcept override;
	[[nodiscard]] HRESULT InvalidateHighlight(std::span<const til::point_span> highlights,
	                                          const TextBuffer& buffer) noexcept override;
	[[nodiscard]] HRESULT InvalidateScroll(const til::point* pcoordDelta) noexcept override;
	[[nodiscard]] HRESULT InvalidateAll() noexcept override;
	[[nodiscard]] HRESULT InvalidateTitle(std::wstring_view proposedTitle) noexcept override;
	[[nodiscard]] HRESULT NotifyNewText(const std::wstring_view newText) noexcept override;
	[[nodiscard]] HRESULT PrepareRenderInfo(RenderFrameInfo info) noexcept override;
	[[nodiscard]] HRESULT ResetLineTransform() noexcept override;
	[[nodiscard]] HRESULT PrepareLineTransform(LineRendition lineRendition, til::CoordType targetRow,
	                                           til::CoordType viewportLeft) noexcept override;
	[[nodiscard]] HRESULT PaintBackground() noexcept override;
	[[nodiscard]] HRESULT PaintBufferLine(std::span<const Cluster> clusters, til::point coord, bool fTrimLeft,
	                                      bool lineWrapped) noexcept override;
	[[nodiscard]] HRESULT PaintBufferGridLines(const GridLineSet lines, const COLORREF gridlineColor,
	                                           const COLORREF underlineColor, const size_t cchLine,
	                                           const til::point coordTarget) noexcept override;
	[[nodiscard]] HRESULT PaintSelection(const til::rect& rect) noexcept override;
	[[nodiscard]] HRESULT PaintCursor(const CursorOptions& options) noexcept override;
	[[nodiscard]] HRESULT UpdateDrawingBrushes(const TextAttribute& textAttributes,
	                                           const RenderSettings& renderSettings, gsl::not_null<IRenderData*> pData,
	                                           bool usingSoftFont, bool isSettingDefaultBrushes) noexcept override;
	[[nodiscard]] HRESULT UpdateFont(const FontInfoDesired& FontInfoDesired, _Out_ FontInfo& FontInfo) noexcept override;
	[[nodiscard]] HRESULT UpdateSoftFont(std::span<const uint16_t> bitPattern, til::size cellSize,
	                                     size_t centeringHint) noexcept override;
	[[nodiscard]] HRESULT UpdateDpi(int iDpi) noexcept override;
	[[nodiscard]] HRESULT UpdateViewport(const til::inclusive_rect& srNewViewport) noexcept override;
	[[nodiscard]] HRESULT GetProposedFont(const FontInfoDesired& FontInfoDesired,
	                                      _Out_ FontInfo& FontInfo,
	                                      int iDpi) noexcept override;
	[[nodiscard]] HRESULT GetDirtyArea(std::span<const til::rect>& area) noexcept override;
	[[nodiscard]] HRESULT GetFontSize(_Out_ til::size* pFontSize) noexcept override;
	[[nodiscard]] HRESULT IsGlyphWideByFont(std::wstring_view glyph, _Out_ bool* pResult) noexcept override;
	[[nodiscard]] HRESULT UpdateTitle(std::wstring_view newTitle) noexcept override;
	void UpdateHyperlinkHoveredId(uint16_t hoveredId) noexcept override;
	// End IRenderEngine

private:

	// FWindowsTerminalAdapter Adapter;
	

};
