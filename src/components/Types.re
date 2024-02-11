module Types = {
  type customFieldsJsCompatible = {activeUsers: Js.Nullable.t(int)};
  type countryJsCompatible = {
    label: string,
    value: string,
    customFields: customFieldsJsCompatible,
  };
  type customFields = {activeUsers: option(int)};
  type country = {
    label: string,
    value: string,
    customFields,
  };
  let countryToCountryJs = (c: country): countryJsCompatible => {
    {
      label: c.label,
      value: c.value,
      customFields: {
        activeUsers: Js.Nullable.fromOption(c.customFields.activeUsers),
      },
    };
  };
  let countryJsToCountry = (c: countryJsCompatible): country => {
    {
      label: c.label,
      value: c.value,
      customFields: {
        activeUsers: Js.Nullable.toOption(c.customFields.activeUsers),
      },
    };
  };
};
