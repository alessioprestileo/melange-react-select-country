module Svg = {
  [@react.component]
  let make =
      (
        ~height: string="14",
        ~width: string="14",
        ~viewBox: string="0 0 14 14",
        ~children,
      ) =>
    <svg
      xmlns="http://www.w3.org/2000/svg"
      height
      width
      viewBox
      fill="none"
      focusable="false"
      role="presentation">
      children
    </svg>;
};
