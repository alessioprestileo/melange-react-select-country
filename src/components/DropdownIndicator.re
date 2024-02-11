open Svg;

module type DropdownIndicator = {
  let render: unit => React.element;
};

module DropdownIndicator: DropdownIndicator = {
  module Styles = {
    let container =
      ReactDOM.Style.make(
        ~height="18px",
        ~width="14px",
        ~display="flex",
        ~alignItems="center",
        ~marginRight="4px",
        (),
      );
  };
  let render = () =>
    <div style=Styles.container>
      <Svg>
        <path
          d="M6 11C7.01929 11 7.96734 10.695 8.75787 10.1713L12.06 13.47L13.47 12.06L10.1713 8.75783C10.695 7.96731 11 7.01927 11 6C11 3.23858 8.76142 1 6 1C3.23858 1 1 3.23858 1 6C1 8.76142 3.23858 11 6 11ZM9.2 6C9.2 7.76731 7.76731 9.2 6 9.2C4.23269 9.2 2.8 7.76731 2.8 6C2.8 4.23269 4.23269 2.8 6 2.8C7.76731 2.8 9.2 4.23269 9.2 6Z"
          fill="#333333"
          fillRule="evenodd"
          clipRule="evenodd"
        />
      </Svg>
    </div>;
};
