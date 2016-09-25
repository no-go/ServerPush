package click.dummer.pushclient;

import android.app.Activity;
import android.view.View;
import android.view.ViewGroup;
import android.widget.BaseAdapter;
import android.widget.TextView;

import java.util.ArrayList;

public class FeedAdapter extends BaseAdapter {
    private ArrayList<Feed> feeds = new ArrayList<>();
    Activity activity;

    // dieser Constructor macht den BaseAdapter Modularer
    FeedAdapter(Activity context) {
        super();
        activity = context;
    }

    public void addItem(Feed item) {
        feeds.add(item);
    }

    public void clear() {
        feeds.clear();
    }

    @Override
    public int getCount() {
        return feeds.size();
    }

    @Override
    public Object getItem(int i) {
        return feeds.get(i);
    }

    @Override
    public long getItemId(int i) {
        return i;
    }

    @Override
    public View getView(int i, View view, ViewGroup viewGroup) {
        view = activity.getLayoutInflater().inflate(R.layout.feed_line, viewGroup, false);
        TextView tt = (TextView) view.findViewById(R.id.line_title);
        TextView tb = (TextView) view.findViewById(R.id.line_body);
        tt.setText(feeds.get(i).title);
        tb.setText(feeds.get(i).body);
        return view;
    }
}