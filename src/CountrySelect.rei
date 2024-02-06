module CountrySelect: {
  [@react.component]
  let make:
    // (~country: option(string), ~onChange: string => unit, ~className: string=? =>
    (~country: option(string), ~onChange: string => unit) =>
    React.element;
};
