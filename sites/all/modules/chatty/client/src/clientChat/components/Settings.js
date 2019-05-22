import React, { useContext, useEffect } from 'react';
import { Query } from 'react-apollo';

import { SettingsContext } from '../context/SettingsContext';
import GET_SETTINGS_QUERY from '../../shared/Apollo/query/getSettings';
import { SET_SETTINGS } from '../context/SettingsContext';

const Settings = ({ children }) => (
  <Query query={GET_SETTINGS_QUERY}>
    {({ data, loading }) => {
      if (!data || loading) return children;

      return (
        <SettingsSetter data={data} loading={loading}>
          {children}
        </SettingsSetter>
      );
    }}
  </Query>
);

const SettingsSetter = ({ children, data, loading }) => {
  const [, dispatch] = useContext(SettingsContext);

  useEffect(() => {
    if (data && !loading) {
      dispatch({
        type: SET_SETTINGS,
        payload: data.settings,
      });
    }
  }, []);

  return children;
};

export default Settings;
