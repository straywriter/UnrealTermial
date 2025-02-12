
#define NOMINMAX





#ifdef _WIN32_WINNT
#undef _WIN32_WINNT
#endif

#include <span>

#pragma warning(push)
#pragma warning(disable : 4100) // '...': unreferenced formal parameter
#pragma warning(disable : 26812) // The enum type '...' is unscoped. Prefer 'enum class' over 'enum' (Enum.3).
#include <base/numerics/safe_math.h>
#pragma warning(pop)


#include <wil/com.h>
#include <wil/filesystem.h>
#include <wil/result_macros.h>
#include <wil/stl.h>
#include <wil/win32_helpers.h>

#include <bit>
#include "gsl/gsl"
#include "til/rect.h"
#include <type_traits>

#include <stdint.h>




// #include "CoreMinimal.h"
//
// THIRD_PARTY_INCLUDES_START
// UE_PUSH_MACRO("check")
#undef check
#undef TEXT

// #include "Windows/PreWindowsApi.h"
// #include "Windows/AllowWindowsPlatformTypes.h"
// #include "Windows/AllowWindowsPlatformAtomics.h"

#include <sal.h>

// This includes support libraries from the CRT, STL, WIL, and GSL
#include "LibraryIncludes.h"



#include <ascii.hpp>

#include "IRenderEngine.hpp"
#include "pch.h"

#include "Terminal.hpp"
// #include "WindowsTerminal-1.21.2361.0/src/renderer/vt/Xterm256Engine.hpp"

namespace Microsoft::Console::VirtualTerminal
{
	class OutputStateMachineEngine;
}

using namespace winrt::Microsoft::Terminal::Core;
using namespace Microsoft::Terminal::Core;

#include <renderer.hpp>
#include "ControlKeyStates.hpp"



#include <OutputStateMachineEngine.hpp>

class DummyRenderer final : public Microsoft::Console::Render::Renderer
{
public:
	Microsoft::Console::Render::RenderSettings _renderSettings;
	
	DummyRenderer(Microsoft::Console::Render::IRenderData* pData = nullptr) :
		Microsoft::Console::Render::Renderer(_renderSettings, pData, nullptr, 0, nullptr) {}

};

#include "Logging/LogMacros.h"
#include "CoreGlobals.h"

#include "test.h"
static void VerifyExpectedString(std::wstring_view expectedString,
								 TextBufferCellIterator& iter)
{
	size_t currentCharIndex = 0;
	for (const auto wch : expectedString)
	{
		// This test spews out a lot of verify logging by default because of
		// the loops, so suppress that to only show the failures.

		wchar_t buffer[]{ wch, L'\0' };
		std::wstring_view view{ buffer, 1 };

		if (view != (iter)->Chars())
		{
			// WEX::Logging::Log::Comment(WEX::Common::NoThrowString().Format(L"character [%d] was mismatched", currentCharIndex));
		}

	}
	// WEX::Logging::Log::Comment(WEX::Common::NoThrowString().Format(
	// 	L"Successfully validated %d characters were '%s'", expectedString.size(), expectedString.data()));
	UE_LOG(LogTemp, Warning, L"Successfully validated %llu characters were '%s'", expectedString.size(), expectedString.data())
};

static TextBufferCellIterator VerifyExpectedString(const TextBuffer& tb,
												   std::wstring_view expectedString,
												   const til::point pos)
{
	auto iter = tb.GetCellDataAt(pos);
	VerifyExpectedString(expectedString, iter);
	return iter;
};

// 将 FString 转换为 std::wstring
std::wstring FStringToWString(const FString& FString)
{
	// 获取 FString 的 TCHAR* 数据
	const TCHAR* TCHARData = *FString;

	// 将 TCHAR* 数据转换为 std::wstring
	std::wstring WString(TCHARData);

	return WString;
}

// #include "IRenderEngine.hpp"

// 将 std::wstring_view 转换为 FString
FString WStringViewToFString(const std::wstring_view& WStringView)
{
	return FString(WStringView.length(), WStringView.data());
}


using namespace Microsoft::Console::Render;

class UERenderEngine1 final : public Microsoft::Console::Render::IRenderEngine
{
public:
	explicit UERenderEngine1(){}

	FString s;

	uint32 row = 0;

	
//         // IRenderEngine
//         [[nodiscard]] HRESULT StartPaint() noexcept override
//         {
//         	
//         	return S_OK;
//         }
//         [[nodiscard]] HRESULT EndPaint() noexcept override
//         {
// 	        
//         	return S_OK;
//         }
//         [[nodiscard]] bool RequiresContinuousRedraw() noexcept override
// 	{
// return true;
// 	}
//         void WaitUntilCanRender() noexcept override
// {
// 		
        // IRenderEngine
        [[nodiscard]] HRESULT StartPaint() noexcept{ return S_OK; }
        [[nodiscard]] HRESULT EndPaint() noexcept{ /*s = ""; row = 0;*/ return S_OK; }
        [[nodiscard]] bool RequiresContinuousRedraw() noexcept{ return S_OK; }
        void WaitUntilCanRender() noexcept{  }
        [[nodiscard]] HRESULT Present() noexcept{ return S_OK; }
        [[nodiscard]] HRESULT ScrollFrame() noexcept{ return S_OK; }
        [[nodiscard]] HRESULT Invalidate(const til::rect* psrRegion) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT InvalidateCursor(const til::rect* psrRegion) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT InvalidateSystem(const til::rect* prcDirtyClient) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT InvalidateSelection(std::span<const til::rect> selections) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT InvalidateHighlight(std::span<const til::point_span> highlights, const TextBuffer& buffer) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT InvalidateScroll(const til::point* pcoordDelta) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT InvalidateAll() noexcept{ return S_OK; }
        [[nodiscard]] HRESULT InvalidateTitle(std::wstring_view proposedTitle) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT NotifyNewText(const std::wstring_view newText) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT PrepareRenderInfo(RenderFrameInfo info) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT ResetLineTransform() noexcept{ return S_OK; }
        [[nodiscard]] HRESULT PrepareLineTransform(LineRendition lineRendition, til::CoordType targetRow, til::CoordType viewportLeft) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT PaintBackground() noexcept{ return S_OK; }
        [[nodiscard]] HRESULT PaintBufferLine(std::span<const Cluster> clusters, til::point coord, bool fTrimLeft, bool lineWrapped) noexcept
	{

		// til::CoordType coord = 0;
		        	for (const auto& cluster : clusters)
		        	{
		        		if(coord.y == row)
		        		{
		        			s += WStringViewToFString(cluster.GetText());
		        		}
				        else
				        {
					        row = coord.y;
				        	s += "\n";
		        			s += WStringViewToFString(cluster.GetText());
				        }
		        		// for ( auto& ch : cluster.GetText())
		        		{
		        		}
		        	}
				// UE_LOG(LogTemp, Log, TEXT("WStringView: %s"), *s);
				return S_OK;
	}
        [[nodiscard]] HRESULT PaintBufferGridLines(const GridLineSet lines, const COLORREF gridlineColor, const COLORREF underlineColor, const size_t cchLine, const til::point coordTarget) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT PaintImageSlice(const ImageSlice& imageSlice, til::CoordType targetRow, til::CoordType viewportLeft) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT PaintSelection(const til::rect& rect) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT PaintCursor(const CursorOptions& options) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT UpdateDrawingBrushes(const TextAttribute& textAttributes, const RenderSettings& renderSettings, gsl::not_null<IRenderData*> pData, bool usingSoftFont, bool isSettingDefaultBrushes) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT UpdateFont(const FontInfoDesired& FontInfoDesired, _Out_ FontInfo& FontInfo) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT UpdateSoftFont(std::span<const uint16_t> bitPattern, til::size cellSize, size_t centeringHint) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT UpdateDpi(int iDpi) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT UpdateViewport(const til::inclusive_rect& srNewViewport) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT GetProposedFont(const FontInfoDesired& FontInfoDesired, _Out_ FontInfo& FontInfo, int iDpi) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT GetDirtyArea(std::span<const til::rect>& area) noexcept
	{

		static constexpr til::rect empty{0, 0, 200, 30};
		area = { &empty, 1 };

		return S_OK;
	}
        [[nodiscard]] HRESULT GetFontSize(_Out_ til::size* pFontSize) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT IsGlyphWideByFont(std::wstring_view glyph, _Out_ bool* pResult) noexcept{ return S_OK; }
        [[nodiscard]] HRESULT UpdateTitle(std::wstring_view newTitle) noexcept{ return S_OK; }
        void UpdateHyperlinkHoveredId(uint16_t hoveredId) noexcept{ }

// }
//         [[nodiscard]] HRESULT Present() noexcept override { return S_OK; }
//         // [[nodiscard]] HRESULT PrepareForTeardown(_Out_ bool* pForcePaint) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT ScrollFrame() noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT Invalidate(const til::rect* psrRegion) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT InvalidateCursor(const til::rect* psrRegion) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT InvalidateSystem(const til::rect* prcDirtyClient) noexcept override { return S_OK; }
//         // [[nodiscard]] HRESULT InvalidateSelection(const std::vector<til::rect>& rectangles) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT InvalidateHighlight(std::span<const til::point_span> highlights, const TextBuffer& buffer) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT InvalidateScroll(const til::point* pcoordDelta) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT InvalidateAll() noexcept override{ return S_OK; }
//         // [[nodiscard]] HRESULT InvalidateFlush(_In_ const bool circled, _Out_ bool* const pForcePaint) noexcept override{ return S_OK; }
//         [[nodiscard]] HRESULT InvalidateTitle(std::wstring_view proposedTitle) noexcept override{ return S_OK; }
//         [[nodiscard]] HRESULT NotifyNewText(const std::wstring_view newText) noexcept override{ return S_OK; }
//         [[nodiscard]] HRESULT PrepareRenderInfo(Microsoft::Console::Render::RenderFrameInfo info) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT ResetLineTransform() noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT PrepareLineTransform(LineRendition lineRendition, til::CoordType targetRow, til::CoordType viewportLeft) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT PaintBackground() noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT PaintBufferLine(std::span<const Microsoft::Console::Render::Cluster> clusters, til::point coord, bool fTrimLeft, bool lineWrapped) noexcept override
//         {
// 		FString s;
//
//         	for (const auto& cluster : clusters)
//         	{
//         		// for ( auto& ch : cluster.GetText())
//         		{
//         			s += WStringViewToFString(cluster.GetText());
//         		}
//         	}
// 		UE_LOG(LogTemp, Log, TEXT("WStringView: %s"), *s);
//
//         	return S_OK;
//         }
//         [[nodiscard]] HRESULT PaintBufferGridLines(const Microsoft::Console::Render::GridLineSet lines, const COLORREF gridlineColor, const COLORREF underlineColor, const size_t cchLine, const til::point coordTarget) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT PaintSelection(const til::rect& rect) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT PaintCursor(const Microsoft::Console::Render::CursorOptions& options) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT UpdateDrawingBrushes(const TextAttribute& textAttributes, const Microsoft::Console::Render::RenderSettings& renderSettings, gsl::not_null<Microsoft::Console::Render::IRenderData*> pData, bool usingSoftFont, bool isSettingDefaultBrushes) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT UpdateFont(const FontInfoDesired& FontInfoDesired, _Out_ FontInfo& FontInfo) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT UpdateSoftFont(std::span<const uint16_t> bitPattern, til::size cellSize, size_t centeringHint) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT UpdateDpi(int iDpi) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT UpdateViewport(const til::inclusive_rect& srNewViewport) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT GetProposedFont(const FontInfoDesired& FontInfoDesired, _Out_ FontInfo& FontInfo, int iDpi) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT GetDirtyArea(std::span<const til::rect>& area) noexcept override {
//         	     // Magic static is only valid because any instance of this object has the same behavior.
//                  // Use member variable instead if this ever changes.
//                  static constexpr til::rect empty{0, 0, 200, 50};
//                  area = { &empty, 1 };
//         
//         return S_OK; }
//         [[nodiscard]] HRESULT GetFontSize(_Out_ til::size* pFontSize) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT IsGlyphWideByFont(std::wstring_view glyph, _Out_ bool* pResult) noexcept override { return S_OK; }
//         [[nodiscard]] HRESULT UpdateTitle(std::wstring_view newTitle) noexcept override { return S_OK; }
//         void UpdateHyperlinkHoveredId(uint16_t hoveredId) noexcept override  { }

	
};

std::wstring stringToWString(const std::string& str) {
	if (str.empty()) {
		return std::wstring();
	}

	// Determine the required buffer size
	size_t size = std::mbstowcs(nullptr, str.c_str(), 0);
	if (size == static_cast<size_t>(-1)) {
		throw std::runtime_error("Error converting string to wstring");
	}

	// Allocate buffer and perform conversion
	std::vector<wchar_t> buffer(size + 1);
	std::mbstowcs(buffer.data(), str.c_str(), size + 1);

	return std::wstring(buffer.data());
}


#include <ftxui/dom/elements.hpp>
#include <ftxui/screen/screen.hpp>



void test()
{
	
	static const til::CoordType TerminalViewWidth = 200;
	static const til::CoordType TerminalViewHeight = 30;
	static const til::CoordType TerminalHistoryLength = 100;
	
	std::unique_ptr<Microsoft::Console::Render::Renderer> emptyRenderer;
	std::unique_ptr<Terminal> term;
	
	term = std::make_unique<Terminal>(Terminal::TestDummyMarker{});
	emptyRenderer = std::make_unique<DummyRenderer>(term.get());
	term->Create({ TerminalViewWidth, TerminalViewHeight }, TerminalHistoryLength, *emptyRenderer);

	// std::wstring testFile = L"testmyh.txt";
	// wil::unique_hfile testFileOut(::CreateFileW(testFile.c_str(), GENERIC_ALL, FILE_SHARE_READ, nullptr, CREATE_ALWAYS, 0, nullptr));
	// auto hFile = wil::unique_hfile(INVALID_HANDLE_VALUE);
	// auto engine = std::make_unique<Microsoft::Console::Render::Xterm256Engine>(std::move(testFileOut), term->GetViewport());
	// emptyRenderer->AddRenderEngine(engine.get());

	auto engine = std::make_unique<UERenderEngine1>();
	emptyRenderer->AddRenderEngine(engine.get());
	
	// auto& termTb = *term->;
	auto& termSm = term->GetStateMachine();
	const auto initialView = term->GetViewport();
	
	// termSm.ProcessString(L"Hello World");
	
	const auto secondView = term->GetViewport();

	auto& termTb = term->GetTextBuffer();

	
	//
	// VerifyExpectedString(termTb, L"Hello World", { 0, 0 });
	
	// termSm.ProcessString(L" sadHello World  asdf29384");
	//
	// auto iter1 = termTb.GetCellDataAt({0 , 0});
	// auto iter2 = termTb.GetCellDataAt({0 , 1});
	// auto iter3 = termTb.GetCellDataAt({0 , 2});
	// auto iter4 = termTb.GetCellDataAt({0 , 3});
	// auto iter5 = termTb.GetCellDataAt({0 , 4});
	//
	// auto iter6 = termTb.GetCellDataAt({1 , 0});
	// auto iter7 = termTb.GetCellDataAt({1 , 1});
	// auto iter8 = termTb.GetCellDataAt({1 , 2});
	// auto iter9 = termTb.GetCellDataAt({1 , 3});
	// auto iter10 = termTb.GetCellDataAt({1 , 4});
	//
	// auto iter11 = termTb.GetCellDataAt({2 , 0});
	// auto iter12 = termTb.GetCellDataAt({2 , 1});
	// auto iter13 = termTb.GetCellDataAt({2 , 2});
	// auto iter14 = termTb.GetCellDataAt({2 , 3});
	// auto iter15 = termTb.GetCellDataAt({2 , 4});
	//

	auto cursor1 = term->GetCursorPosition();
	// const auto eraseAll = L"\nasd\n";
	termSm.ProcessString(L"123asdfdas我们");


	
	termSm.ProcessString(L"\r\n123asdf");
	const auto eraseAll = L"\033[2J\033[H";

	// termSm.SetParserMode()

	
	termSm.ProcessString(L"bar\r\nbar\r\nbar\r\n");

	using namespace ftxui;

 
	// Define the document
	// Element document =
	//   hbox({
	// 	text("left")   | borderLight,
	// 	text("middle") | borderLight,
	// 	text("right")  | borderLight,
	//   });
 //
	// auto screen = Screen::Create(
	//   Dimension::Full(),       // Width
	//   Dimension::Fit(document) // Height
	// );
	// Render(screen, document);
	// //screen.Print();
	// auto sss = screen.ToString();
	// auto ws = to_wstring(sss);
	// termSm.ProcessString(ws);

	using namespace ftxui;
	auto make_box = [](int dimx, int dimy) {
		std::string title = std::to_string(dimx) + "x" + std::to_string(dimy);
		return window(text(title) | hcenter | bold,
					  text("content") | hcenter | dim) |
			   size(WIDTH, EQUAL, dimx) | size(HEIGHT, EQUAL, dimy);
	};

	auto style = size(WIDTH, GREATER_THAN, 20) | borderLight |
				 size(HEIGHT, GREATER_THAN, 30) | size(WIDTH, LESS_THAN, 50);

	auto document = hflow({
						make_box(7, 7),
						make_box(7, 5),
						make_box(5, 7),
						make_box(10, 4),
						make_box(10, 4),
						make_box(10, 4),
						make_box(10, 4),
						make_box(11, 4),
						make_box(11, 4),
						make_box(11, 4),
						make_box(11, 4),
						make_box(12, 4),
						make_box(12, 5),
						make_box(12, 4),
						make_box(13, 4),
						make_box(13, 3),
						make_box(13, 3),
						make_box(10, 3),
					}) |
					style;

	auto screen = Screen::Create(Dimension::Full(), Dimension::Fit(document));
	Render(screen, document);
	auto sss = screen.ToString();
	auto ws = to_wstring(sss);
	termSm.ProcessString(ws);
	screen.Print();
	// getchar();


	// termSm.Engine().ActionClear();

	// auto b = termSm.FlushToTerminal();

	auto cursor2 = term->GetCursorPosition();

	// term->EraseScrollback();

	// termSm.ProcessString(eraseAll);
	//
	// auto& engine = reinterpret_cast<Microsoft::Console::VirtualTerminal::OutputStateMachineEngine&>(termSm.Engine());
	// engine.Dispatch().EraseInDisplay(Microsoft::Console::VirtualTerminal::DispatchTypes::EraseType::FromBeginning);
	// termSm.ResetState();
	// termSm.Engine().ActionDcsDispatch()

	// for(auto i = 0; i < 10; i++)
	// {
	// 	termSm.ProcessString(L"\nX");
	// }
	// termSm.ProcessCharacter(Microsoft::Console::VirtualTerminal::AsciiChars::ESC);
	// term->SetViewportPosition({0, 0});

	// term->UserScrollViewport(2);
	// auto ps = CreateChildProcessAndGetOutput(FString(TEXT("D:\\Applications\\Scoop\\shims\\nvim.exe")), FString(TEXT("")));
	auto ps = CreateChildProcessAndGetOutput(FString(TEXT("D:\\Applications\\Scoop\\shims\\nvim.exe")), FString(TEXT("")));
	std::cout << TCHAR_TO_UTF8(*ps);

	termSm.ProcessString(FStringToWString(ps));
	
	auto o = emptyRenderer->PaintFrame();

	UE_LOG(LogTemp, Log, TEXT("\n%s"), *engine->s);
	
	// termSm.ProcessString(eraseAll);
	// term->UserScrollViewport(2);
		// termSm.ProcessString(L"Hello World\x1b[2J \x1b[2J");
	
	UE_LOG(LogTemp, Log, TEXT("=================================="));

	// term->UserScrollViewport(1);
	//
	// termSm.ProcessString(L"我们新的测试开始");
	// auto o2 = emptyRenderer->PaintFrame();
	
	
	auto v = term->GetViewport();
	// term->SetViewportPosition({0, 0});
	// termTb.IncrementCircularBuffer();
	auto v2 = term->GetViewport();
	// termSm.ProcessString(L"123asdf");

	// term->UserScrollViewport(2);
	
	auto v3 = term->GetViewport();

	// auto& c = termTb.GetCursor();
	// c.SetPosition({0,0});
	//
	// termSm.ProcessString(L"123asdf\n sadf");
	
	// termTb.FillRect({ 0, 0, 5, 2 }, L"L", termTb.GetCurrentAttributes());

	using Microsoft::Terminal::Core::ControlKeyStates;

	auto in = term->SendCharEvent(L'a', 0, ControlKeyStates::LeftAltPressed);
	
	auto xiter1 = termTb.GetCellDataAt({0 , 0});
	auto xiter2 = termTb.GetCellDataAt({0 , 1});
	auto xiter3 = termTb.GetCellDataAt({0 , 2});
	auto xiter4 = termTb.GetCellDataAt({0 , 3});
	auto xiter5 = termTb.GetCellDataAt({0 , 4});
	auto xiter6 = termTb.GetCellDataAt({0 , 5});

	term->SerializeMainBuffer(L"123asd.txt");

	
	
	
}
